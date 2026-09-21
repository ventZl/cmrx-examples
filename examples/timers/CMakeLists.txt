add_application(app app.c)
target_link_libraries(app stdlib)
target_add_applications(${EXAMPLE} app)
