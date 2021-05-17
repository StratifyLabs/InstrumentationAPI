
set(DEPENDENCIES TestAPI FsAPI JsonAPI InstrumentationAPI)

api_add_test_executable(InstrumentationAPI 32768 "${DEPENDENCIES}")



