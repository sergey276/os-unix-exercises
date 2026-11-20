# UNIX system programming exercises

Lab exercises from the Operating Systems course at TU Košice, written in C for Linux. Each exercise folder contains the program(s) and a short text report (`*_doc.txt` / `*.txt`) describing what was tested and observed.

| Folder | Topic |
|---|---|
| `T02` | File I/O basics (`open` flags such as `O_CREAT`, reading and writing) |
| `T03` | File descriptors and file access (`open`, flags, permissions) |
| `T04` | File permissions (setuid/setgid/sticky bit, ACLs, capabilities), terminal settings (`termios`) |
| `T05` | Environment variables, `fork`, `exec*`, `dup2`, signals (`sigaction`) |
| `TO7` | Pipes |
| `TO8` | Shared memory |
| `T09` | Synchronisation of two processes through shared memory: flag, file, FIFO, semaphores |
| `T10` | TCP sockets (`p1_tcp.c`, `p2_tcp.c`) |

## Build

```bash
gcc -Wall -o p1 p1_flag.c && gcc -Wall -o p2 p2_flag.c
```

Requires Linux (POSIX APIs).

## License

MIT, see [LICENSE](LICENSE).
