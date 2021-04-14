#include <Nazara/Core.hpp>
#include <Nazara/Platform.hpp>
#include <Nazara/Renderer.hpp>
#include <Nazara/Shader.hpp>
#include <Nazara/Shader/SpirvConstantCache.hpp>
#include <Nazara/Shader/SpirvPrinter.hpp>
#include <Nazara/Utility.hpp>
#include <array>
#include <iostream>

const char shaderSource[] = R"(
[[layout(std140)]]
struct Data
{
	projectionMatrix: mat4<f32>,
	worldMatrix: mat4<f32>,
	viewMatrix: mat4<f32>
}

external
{
	[[binding(0)]] viewerData: uniform<Data>,
	[[binding(1)]] tex: sampler2D<f32>
}

struct VertIn
{
	[[location(0)]] position: vec3<f32>,
	[[location(1)]] normal: vec3<f32>,
	[[location(2)]] uv: vec2<f32>
}

struct VertOut
{
	[[builtin(position)]] position: vec4<f32>,
	[[location(0)]] normal: vec3<f32>,
	[[location(1)]] uv: vec2<f32>
}

struct FragOut
{
	[[location(0)]] color: vec4<f32>
}

[[entry(frag)]]
fn main(fragIn: VertOut) -> FragOut
{
	let lightDir = vec3<f32>(0.0, -0.707, 0.707);
	let lightFactor = dot(fragIn.normal, lightDir);

	let fragOut: FragOut;
	fragOut.color = lightFactor * tex.Sample(fragIn.uv);

	return fragOut;
}

[[entry(vert)]]
fn main(vertIn: VertIn) -> VertOut
{
	let vertOut: VertOut;
	vertOut.position = viewerData.projectionMatrix * viewerData.viewMatrix * viewerData.worldMatrix * vec4<f32>(vertIn.position, 1.0);
	vertOut.normal = vertIn.normal;
	vertOut.uv = vertIn.uv;

	return vertOut;
}
)";

int main()
{
	Nz::Renderer::Config rendererConfig;
	std::cout << "Run using Vulkan? (y/n)" << std::endl;
	if (std::getchar() == 'y')
		rendererConfig.preferredAPI = Nz::RenderAPI::Vulkan;
	else
		rendererConfig.preferredAPI = Nz::RenderAPI::OpenGL;

	Nz::Modules<Nz::Renderer> nazara(rendererConfig);

	Nz::RenderWindow window;

	Nz::MeshParams meshParams;
	meshParams.matrix = Nz::Matrix4f::Rotate(Nz::EulerAnglesf(0.f, 90.f, 180.f)) * Nz::Matrix4f::Scale(Nz::Vector3f(0.002f));
	meshParams.vertexDeclaration = Nz::VertexDeclaration::Get(Nz::VertexLayout_XYZ_Normal_UV);

	std::string windowTitle = "Render Test";
	if (!window.Create(Nz::VideoMode(800, 600, 32), windowTitle))
	{
		std::cout << "Failed to create Window" << std::endl;
		return __LINE__;
	}

	std::shared_ptr<Nz::RenderDevice> device = window.GetRenderDevice();

	auto fragVertShader = device->InstantiateShaderModule(Nz::ShaderStageType::Fragment | Nz::ShaderStageType::Vertex, Nz::ShaderLanguage::NazaraShader, shaderSource, sizeof(shaderSource));
	if (!fragVertShader)
	{
		std::cout << "Failed to instantiate shader" << std::endl;
		return __LINE__;
	}

	Nz::MeshRef drfreak = Nz::Mesh::LoadFromFile("resources/Spaceship/spaceship.obj", meshParams);
	if (!drfreak)
	{
		NazaraError("Failed to load model");
		return __LINE__;
	}

	Nz::StaticMesh* drfreakMesh = static_cast<Nz::StaticMesh*>(drfreak->GetSubMesh(0));

	const Nz::VertexBuffer* drfreakVB = drfreakMesh->GetVertexBuffer();
	const Nz::IndexBuffer* drfreakIB = drfreakMesh->GetIndexBuffer();

	// Index buffer
	std::cout << "Index count: " << drfreakIB->GetIndexCount() << std::endl;

	// Vertex buffer
	std::cout << "Vertex count: " << drfreakVB->GetVertexCount() << std::endl;

	// Texture
	Nz::ImageRef drfreakImage = Nz::Image::LoadFromFile("resources/Spaceship/Texture/diffuse.png");
	if (!drfreakImage || !drfreakImage->Convert(Nz::PixelFormat_RGBA8))
	{
		NazaraError("Failed to load image");
		return __LINE__;
	}

	Nz::TextureInfo texParams;
	texParams.pixelFormat = drfreakImage->GetFormat();
	texParams.type = drfreakImage->GetType();
	texParams.width = drfreakImage->GetWidth();
	texParams.height = drfreakImage->GetHeight();
	texParams.depth = drfreakImage->GetDepth();

	std::shared_ptr<Nz::Texture> texture = device->InstantiateTexture(texParams);
	if (!texture->Update(drfreakImage->GetConstPixels()))
	{
		NazaraError("Failed to update texture");
		return __LINE__;
	}

	std::shared_ptr<Nz::TextureSampler> textureSampler = device->InstantiateTextureSampler({});

	struct
	{
		Nz::Matrix4f projectionMatrix;
		Nz::Matrix4f modelMatrix;
		Nz::Matrix4f viewMatrix;
	}
	ubo;

	Nz::Vector2ui windowSize = window.GetSize();
	ubo.projectionMatrix = Nz::Matrix4f::Perspective(70.f, float(windowSize.x) / windowSize.y, 0.1f, 1000.f);
	ubo.viewMatrix = Nz::Matrix4f::Translate(Nz::Vector3f::Backward() * 1);
	ubo.modelMatrix = Nz::Matrix4f::Translate(Nz::Vector3f::Forward() * 2 + Nz::Vector3f::Right());

	Nz::UInt32 uniformSize = sizeof(ubo);

	Nz::RenderPipelineLayoutInfo pipelineLayoutInfo;
	auto& uboBinding = pipelineLayoutInfo.bindings.emplace_back();
	uboBinding.index = 0;
	uboBinding.shaderStageFlags = Nz::ShaderStageType::Vertex;
	uboBinding.type = Nz::ShaderBindingType::UniformBuffer;

	auto& textureBinding = pipelineLayoutInfo.bindings.emplace_back();
	textureBinding.index = 1;
	textureBinding.shaderStageFlags = Nz::ShaderStageType::Fragment;
	textureBinding.type = Nz::ShaderBindingType::Texture;

	std::shared_ptr<Nz::RenderPipelineLayout> renderPipelineLayout = device->InstantiateRenderPipelineLayout(std::move(pipelineLayoutInfo));

	Nz::ShaderBindingPtr shaderBinding = renderPipelineLayout->AllocateShaderBinding();

	std::shared_ptr<Nz::AbstractBuffer> uniformBuffer = device->InstantiateBuffer(Nz::BufferType_Uniform);
	if (!uniformBuffer->Initialize(uniformSize, Nz::BufferUsage_DeviceLocal | Nz::BufferUsage_Dynamic))
	{
		NazaraError("Failed to create uniform buffer");
		return __LINE__;
	}

	shaderBinding->Update({
		{
			0,
			Nz::ShaderBinding::UniformBufferBinding {
				uniformBuffer.get(), 0, uniformSize
			}
		},
		{
			1,
			Nz::ShaderBinding::TextureBinding {
				texture.get(), textureSampler.get()
			}
		}
	});

	Nz::RenderPipelineInfo pipelineInfo;
	pipelineInfo.pipelineLayout = renderPipelineLayout;

	pipelineInfo.depthBuffer = true;
	pipelineInfo.shaderModules.emplace_back(fragVertShader);

	auto& vertexBuffer = pipelineInfo.vertexBuffers.emplace_back();
	vertexBuffer.binding = 0;
	vertexBuffer.declaration = drfreakVB->GetVertexDeclaration();

	std::shared_ptr<Nz::RenderPipeline> pipeline = device->InstantiateRenderPipeline(pipelineInfo);

	Nz::RenderDevice* renderDevice = window.GetRenderDevice().get();

	Nz::RenderWindowImpl* windowImpl = window.GetImpl();
	std::shared_ptr<Nz::CommandPool> commandPool = windowImpl->CreateCommandPool(Nz::QueueType::Graphics);

	Nz::RenderBuffer* renderBufferIB = static_cast<Nz::RenderBuffer*>(drfreakIB->GetBuffer()->GetImpl());
	Nz::RenderBuffer* renderBufferVB = static_cast<Nz::RenderBuffer*>(drfreakVB->GetBuffer()->GetImpl());

	if (!renderBufferIB->Synchronize(renderDevice))
	{
		NazaraError("Failed to synchronize render buffer");
		return __LINE__;
	}

	if (!renderBufferVB->Synchronize(renderDevice))
	{
		NazaraError("Failed to synchronize render buffer");
		return __LINE__;
	}

	Nz::AbstractBuffer* indexBufferImpl = renderBufferIB->GetHardwareBuffer(renderDevice);
	Nz::AbstractBuffer* vertexBufferImpl = renderBufferVB->GetHardwareBuffer(renderDevice);

	Nz::CommandBufferPtr drawCommandBuffer;
	auto RebuildCommandBuffer = [&]
	{
		Nz::Vector2ui windowSize = window.GetSize();

		drawCommandBuffer = commandPool->BuildCommandBuffer([&](Nz::CommandBufferBuilder& builder)
		{
			Nz::Recti renderRect(0, 0, window.GetSize().x, window.GetSize().y);

			Nz::CommandBufferBuilder::ClearValues clearValues[2];
			clearValues[0].color = Nz::Color::Black;
			clearValues[1].depth = 1.f;
			clearValues[1].stencil = 0;

			builder.BeginDebugRegion("Main window rendering", Nz::Color::Green);
			{
				builder.BeginRenderPass(windowImpl->GetFramebuffer(), windowImpl->GetRenderPass(), renderRect, { clearValues[0], clearValues[1] });
				{
					builder.BindIndexBuffer(indexBufferImpl);
					builder.BindPipeline(*pipeline);
					builder.BindVertexBuffer(0, vertexBufferImpl);
					builder.BindShaderBinding(*shaderBinding);

					builder.SetScissor(Nz::Recti{ 0, 0, int(windowSize.x), int(windowSize.y) });
					builder.SetViewport(Nz::Recti{ 0, 0, int(windowSize.x), int(windowSize.y) });

					builder.DrawIndexed(drfreakIB->GetIndexCount());
				}
				builder.EndRenderPass();
			}
			builder.EndDebugRegion();
		});
	};
	RebuildCommandBuffer();


	Nz::Vector3f viewerPos = Nz::Vector3f::Zero();

	Nz::EulerAnglesf camAngles(0.f, 0.f, 0.f);
	Nz::Quaternionf camQuat(camAngles);

	window.EnableEventPolling(true);

	Nz::Clock updateClock;
	Nz::Clock secondClock;
	unsigned int fps = 0;
	bool uboUpdate = true;

	Nz::Mouse::SetRelativeMouseMode(true);

	while (window.IsOpen())
	{
		Nz::WindowEvent event;
		while (window.PollEvent(&event))
		{
			switch (event.type)
			{
				case Nz::WindowEventType_Quit:
					window.Close();
					break;

				case Nz::WindowEventType_MouseMoved: // La souris a bougé
				{
					// Gestion de la caméra free-fly (Rotation)
					float sensitivity = 0.3f; // Sensibilité de la souris

					// On modifie l'angle de la caméra grâce au déplacement relatif sur X de la souris
					camAngles.yaw = Nz::NormalizeAngle(camAngles.yaw - event.mouseMove.deltaX*sensitivity);

					// Idem, mais pour éviter les problèmes de calcul de la matrice de vue, on restreint les angles
					camAngles.pitch = Nz::Clamp(camAngles.pitch + event.mouseMove.deltaY*sensitivity, -89.f, 89.f);

					camQuat = camAngles;
					
					uboUpdate = true;
					break;
				}

				case Nz::WindowEventType_Resized:
				{
					Nz::Vector2ui windowSize = window.GetSize();
					ubo.projectionMatrix = Nz::Matrix4f::Perspective(70.f, float(windowSize.x) / windowSize.y, 0.1f, 1000.f);
					uboUpdate = true;
					break;
				}

				default:
					break;
			}
		}

		if (updateClock.GetMilliseconds() > 1000 / 60)
		{
			float cameraSpeed = 2.f * updateClock.GetSeconds();
			updateClock.Restart();

			if (Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::Up) || Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::Z))
				viewerPos += camQuat * Nz::Vector3f::Forward() * cameraSpeed;

			// Si la flèche du bas ou la touche S est pressée, on recule
			if (Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::Down) || Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::S))
				viewerPos += camQuat * Nz::Vector3f::Backward() * cameraSpeed;

			// Etc...
			if (Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::Left) || Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::Q))
				viewerPos += camQuat * Nz::Vector3f::Left() * cameraSpeed;

			// Etc...
			if (Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::Right) || Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::D))
				viewerPos += camQuat * Nz::Vector3f::Right() * cameraSpeed;

			// Majuscule pour monter, notez l'utilisation d'une direction globale (Non-affectée par la rotation)
			if (Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::LShift) || Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::RShift))
				viewerPos += Nz::Vector3f::Up() * cameraSpeed;

			// Contrôle (Gauche ou droite) pour descendre dans l'espace global, etc...
			if (Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::LControl) || Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::RControl))
				viewerPos += Nz::Vector3f::Down() * cameraSpeed;

			uboUpdate = true;
		}

		Nz::RenderFrame frame = windowImpl->Acquire();
		if (!frame)
			continue;

		if (frame.IsFramebufferInvalidated())
			RebuildCommandBuffer();

		ubo.viewMatrix = Nz::Matrix4f::ViewMatrix(viewerPos, camAngles);

		if (uboUpdate)
		{
			auto& allocation = frame.GetUploadPool().Allocate(uniformSize);

			std::memcpy(allocation.mappedPtr, &ubo, sizeof(ubo));

			frame.Execute([&](Nz::CommandBufferBuilder& builder)
			{
				builder.BeginDebugRegion("UBO Update", Nz::Color::Yellow);
				{
					builder.PreTransferBarrier();
					builder.CopyBuffer(allocation, uniformBuffer.get());
					builder.PostTransferBarrier();
				}
				builder.EndDebugRegion();
			}, Nz::QueueType::Transfer);

			uboUpdate = false;
		}

		frame.SubmitCommandBuffer(drawCommandBuffer.get(), Nz::QueueType::Graphics);

		frame.Present();

		window.Display();

		// On incrémente le compteur de FPS improvisé
		fps++;

		if (secondClock.GetMilliseconds() >= 1000) // Toutes les secondes
		{
			// Et on insère ces données dans le titre de la fenêtre
			window.SetTitle(windowTitle + " - " + Nz::NumberToString(fps) + " FPS");

			/*
			Note: En C++11 il est possible d'insérer de l'Unicode de façon standard, quel que soit l'encodage du fichier,
			via quelque chose de similaire à u8"Cha\u00CEne de caract\u00E8res".
			Cependant, si le code source est encodé en UTF-8 (Comme c'est le cas dans ce fichier),
			cela fonctionnera aussi comme ceci : "Chaîne de caractères".
			*/

			// Et on réinitialise le compteur de FPS
			fps = 0;

			// Et on relance l'horloge pour refaire ça dans une seconde
			secondClock.Restart();
		}
	}

	return EXIT_SUCCESS;
}
