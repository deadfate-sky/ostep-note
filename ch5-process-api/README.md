# ch5 Interlude: Process API

- CRUX: HOW TO CREATE AND CONTROL PROCESSES
  - What interfaces should the OS present for process creation and control? 
  - How should these interfaces be designed to enable powerful functionality, ease of use, and high performance?

## 5.1 The `fork()` System Call
- `fork()` 產生一個跟原本的 process 幾乎一樣的 process
- 不過產生的 child process 並不會執行正個 `main()`，所以 `printf("hello world (pid:%d)\n", (int)getpid());` 的 `hello world` 只出現一次。
  - 目前看起來 child process 的執行結果看來很像是從 `rc = fork()` ，也就是他誕生的該行開始執行下一行。
- 基於是 parent 還是 child， `fork()` 會 return 不同的值。
    - parent: `rc` 會是 child process 的 pid。因此可以看到他流程走到 ` printf("hello, I am parent of %d (pid:%d)\n", rc, (int)getpid());` 這行。
    - child: `rc` 會是 0，因此流程走向另一個結果， print `hello, I am child (pid:%d)`。
- CPU scheduler 會決定哪個 process 先執行，`non-determinism`。


## 5.2 The `wait()` System Call
- 在 `p2.c` 的程式中，即使是 parent process 先執行，也會遇到 `int wc = wait(NULL);` 這行。此時， parent process 會等到 child process 先執行完，再接著繼續執行。
- 根據 GNU C 語言的手冊，`wait()` 也是 multi-threaded programs 的 cancellation point。

## 5.3 Finally, the exec() System Call
- "Thus, it does not create a new process; rather, it transforms the currently running program (formerly p3) into a different running program (wc)."
  - 原本 `fork()` 之後的 child process，透過 `exec()` 把現在 child process 轉換成執行 `wc` process。
  - 執行成功的 `exec()` 不會 return，因此 `printf("this shouldn't print out");` 不會 print 出來。
- "This section describes the exec family of functions, for executing a file as a process image. You can use these functions to make a child process execute a new program after it has been forked."
  - 另外根據 GNU C 語言手冊， `exec()` 可用於使 `fork()` 後的 child process 執行其他 program。  
- C語言複習 []()

## 5.4 Why? Motivating the API