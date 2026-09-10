add_application(app app.c)
target_link_libraries(app stdlib)

add_application(init init.c)
target_link_libraries(init stdlib)

target_add_applications(${EXAMPLE} app init)

