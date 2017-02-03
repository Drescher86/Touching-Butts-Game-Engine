IF(WIN32)
    FIND_PATH( LUABRIDGE_INCLUDE_DIR
            NAMES
				LuaBridge.h
            PATHS
                $ENV{PROGRAMFILES}/LuaBridge
                ${LUABRIDGE_ROOT_DIR}
                $ENV{LUABRIDGE_ROOT_DIR}/include
                $ENV{LUABRIDGE_ROOT_DIR}
				
                DOC "The directory where LuaBridge.h resides")
ELSE(WIN32)
    FIND_PATH( LUABRIDGE_INCLUDE_DIR
            NAMES
                LuaBridge.h
            PATHS
                /usr/include
                /usr/local/include
                /sw/include
                /opt/local/include
                ${LUABRIDGE_ROOT_DIR}
                $ENV{LUABRIDGE_ROOT_DIR}/include
                $ENV{LUABRIDGE_ROOT_DIR}
                DOC "The directory where LuaBridge.h resides"
            )
ENDIF(WIN32)


IF(LUABRIDGE_INCLUDE_DIR)
    SET(LUABRIDGE_FOUND "YES")
    MESSAGE(STATUS "Found LUABridge.")
ENDIF(LUABRIDGE_INCLUDE_DIR)