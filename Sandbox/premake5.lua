project "Sandbox"
	kind "ConsoleApp"
	files { "**.cpp", "**.h", "**.hpp" }
	links {
		"Hangar"
	}
	includedirs {
		"%{wks.location}"
	}