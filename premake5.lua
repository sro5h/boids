--==============================================================================
-- ICARUS build script
--------------------------------------------------------------------------------
-- View the README.md for further information
-- premake5.lua
--==============================================================================

--------------------------------------------------------------------------------
-- Declare core globals
--------------------------------------------------------------------------------
DIRECTORY_BUILD         = ".build/"
DIRECTORY_BIN           = DIRECTORY_BUILD .. ".bin/"
DIRECTORY_SOURCE        = "src/"
DIRECTORY_INCLUDE       = "src/"
DIRECTORY_LIBS          = "libs/"
-- Workspace and project settings
WORKSPACE_BOIDS         = "ws_boids"
PROJECT_BOIDS           = "boids"
-- !core globals ---------------------------------------------------------------

--------------------------------------------------------------------------------
-- Declare dependency roots
--------------------------------------------------------------------------------
-- Dependency directories
ROOT_LIBS               = ""

if _ACTION == "vs2012" then
    ROOT_LIBS           = DIRECTORY_LIBS .. "vs2012-32/"
elseif _ACTION == "vs2013" then
    ROOT_LIBS           = DIRECTORY_LIBS .. "vs2013-32/"
end

ROOT_SFML               = ROOT_LIBS .. "SFML/"
-- !dependency roots -----------------------------------------------------------

--------------------------------------------------------------------------------
-- Set dependency directories
--------------------------------------------------------------------------------
BOIDS_LIB               = {
                            ROOT_SFML .. "lib"
}
BOIDS_INCLUDE           = {
                            DIRECTORY_INCLUDE,
                            ROOT_SFML .. "include"
}
BOIDS_LINKS_DEBUG       = {
                            -- SFML
                            "sfml-system-s-d",
                            "sfml-window-s-d",
                            "winmm",
                            "opengl32",
                            "freetype",
                            "jpeg",
                            "sfml-graphics-s-d"
}
BOIDS_LINKS_RELEASE     = {
                            -- SFML
                            "winmm",
                            "sfml-system-s",
                            "opengl32",
                            "sfml-window-s",
                            "freetype",
                            "jpeg",
                            "sfml-graphics-s"
}
-- !dependency directories -----------------------------------------------------

--------------------------------------------------------------------------------
-- Declare workspace
--------------------------------------------------------------------------------
workspace ( WORKSPACE_BOIDS )
    configurations ( { "Debug", "Release" } )
    location ( DIRECTORY_BUILD )
    defines ( { "SFML_STATIC" } )

    ----------------------------------------------------------------------------
    -- Declare project core_client
    ----------------------------------------------------------------------------
    project ( PROJECT_BOIDS )
        kind ( "ConsoleApp" )
        language ( "C++" )
        includedirs ( BOIDS_INCLUDE )
        libdirs ( BOIDS_LIB )
        location ( DIRECTORY_BUILD .. PROJECT_BOIDS )
        targetdir ( DIRECTORY_BIN .. PROJECT_BOIDS .. "/%{cfg.buildcfg}" )
        files ( { DIRECTORY_INCLUDE .. "**.h", DIRECTORY_SOURCE .. "**.cpp" } )

        ------------------------------------------------------------------------
        -- Declare filters
        ------------------------------------------------------------------------
        -- Debug
        ------------------------------------------------------------------------
        filter ( "configurations:Debug" )
            defines ( { "BOIDS_DEBUG" } )
            flags ( { "Symbols" } )
            links ( BOIDS_LINKS_DEBUG )
        -- Release
        ------------------------------------------------------------------------
        filter ( "configurations:Release" )
            defines ( { "BOIDS_RELEASE" } )
            optimize ( "On" )
            links ( BOIDS_LINKS_RELEASE )
        -- !filters ------------------------------------------------------------
    -- !project core_client ----------------------------------------------------
-- !workspace ------------------------------------------------------------------

--==============================================================================
-- !premake5.lua
--==============================================================================
