add_application(rpcserver rpc.c)
target_link_libraries(rpcserver stdlib)

add_application(client client.c)
target_link_libraries(client stdlib)

target_add_applications(${EXAMPLE} rpcserver client)
