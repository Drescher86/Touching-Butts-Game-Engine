#

# Try to find SimpleRenderEngine library and include path.
# Once done this will define
#
# SRE_FOUND
# SRE_INCLUDE_DIR
# SRE_LIBRARY
#
IF(WIN32)
    FIND_PATH( LUA_INCLUDE_DIR
            NAMES
				LUA.h
            PATHS
                $ENV{PROGRAMFILES}/LUA
                ${LUA_ROOT_DIR}
                $ENV{LUA_ROOT_DIR}/include
                $ENV{LUA_ROOT_DIR}
                DOC "The directory where LUA.h resides")
	
ELSE(WIN32)
    FIND_PATH( LUA_INCLUDE_DIR
            NAMES
                LUA.h
            PATHS
                /usr/include
                /usr/local/include
                /sw/include
                /opt/local/include
                ${LUA_ROOT_DIR}
                $ENV{LUA_ROOT_DIR}/include
                $ENV{LUA_ROOT_DIR}
                DOC "The directory where LUA.h resides"
            )
ENDIF(WIN32)



find_library( LUA_LIBRARY
        NAMES
            lua53
        PATHS
            ${LUA_LOCATION}/lib
			$ENV{LUA_LOCATION}
            DOC "The LUA library")

IF(LUA_INCLUDE_DIR)
    SET(LUA_FOUND "YES")
    MESSAGE(STATUS "Found LUA.")
ENDIF(LUA_INCLUDE_DIR)
