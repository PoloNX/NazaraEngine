target("Pong")
	add_deps("NazaraGraphics")
	add_packages("entt")
	add_files("**.cpp")
    add_headerfiles("**.hpp")
	add_defines("NAZARA_ENTT")