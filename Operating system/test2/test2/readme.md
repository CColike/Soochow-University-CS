## IPC文件夹

game_msgq.c（用消息机制来实现IPC）

```
gcc game_msgq.c -o game_msgq
./game_msgq
```

##### game_socket文件夹（用套接字来实现IPC）

```
gcc caipan.c    -o caipan
gcc xuanshou1.c -o xuanshou1
gcc xuanshou2.c -o xuanshou2
(在3个不同的终端中依次执行以下命令)
./caipan
./xuanshou1
./xuanshou2
```



## SYNC文件夹

sync.c（解决生产者消费者问题）：

```
gcc sync.c -lpthread -o sync
./sync
```



