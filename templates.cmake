
message(STATUS "Generating files")

file(READ ./include/version.h version_h_content)
string(REGEX MATCH "#define PRODUCT_VERSION_CODE ([0-9]+)" unused "${version_h_content}")
set(PRODUCT_VERSION_CODE ${CMAKE_MATCH_1})
string(REGEX MATCH "#define PRODUCT_VERSION \"([^\"]+)\"" unused "${version_h_content}")
set(PRODUCT_VERSION ${CMAKE_MATCH_1})

function(create_from_template target)
    message(STATUS "  ${target}")
    set(template "${target}.template")

    file(READ ${template} template_content)
    string(REPLACE "PRODUCT_VERSION_CODE" "${PRODUCT_VERSION_CODE}" template_content "${template_content}")
    string(REPLACE "PRODUCT_VERSION" "${PRODUCT_VERSION}" template_content "${template_content}")
    file(WRITE ${target} "${template_content}")
endfunction()

create_from_template("./gui/info.ui")
create_from_template("./windows/SyncMyL2P.xml")
create_from_template("./osx/Info.plist")