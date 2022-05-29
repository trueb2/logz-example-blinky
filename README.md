# Zephyr RTOS application + Rust static library

This example builds a basic blinky application with some perodic blinking, logging, and simd math. Both C and Rust implement logging and simd functionality with the Rust library backed by `logz` registering a logger via `SYS_INIT`


### Example output

```
[00:00:11.902,313] <inf> blinky: LED: 0
[00:00:11.902,313] <inf> blinky: A: 2e5c8ab8 B:  1020304, C: 2f5e8dbc
[00:00:11.902,374] <dbg> rs: log_dbg: logz_example_rs: Foo
[00:00:11.902,435] <dbg> rs: log_dbg: logz_example_rs: Bar
[00:00:11.902,465] <inf> rs: logz_example_rs: Fizz
[00:00:11.902,496] <wrn> rs: logz_example_rs: Buzz
[00:00:11.902,557] <err> rs: logz_example_rs: Fizzle
[00:00:11.902,618] <inf> rs: logz_example_rs: A: 0x2e5c8ab8 B: 0x1020304 C: 0x2f5e8dbc
[00:00:12.152,313] <inf> blinky: LED: 1
[00:00:12.152,343] <inf> blinky: A: 2f5e8dbc B:  1020304, C: 306090c0
[00:00:12.152,404] <dbg> rs: log_dbg: logz_example_rs: Foo
[00:00:12.152,435] <dbg> rs: log_dbg: logz_example_rs: Bar
[00:00:12.152,465] <inf> rs: logz_example_rs: Fizz
[00:00:12.152,526] <wrn> rs: logz_example_rs: Buzz
[00:00:12.152,557] <err> rs: logz_example_rs: Fizzle
[00:00:12.152,618] <inf> rs: logz_example_rs: A: 0x2f5e8dbc B: 0x1020304 C: 0x306090c0
[00:00:12.402,313] <inf> blinky: LED: 0
[00:00:12.402,313] <inf> blinky: A: 306090c0 B:  1020304, C: 316293c4
[00:00:12.402,374] <dbg> rs: log_dbg: logz_example_rs: Foo
[00:00:12.402,435] <dbg> rs: log_dbg: logz_example_rs: Bar
[00:00:12.402,465] <inf> rs: logz_example_rs: Fizz
[00:00:12.402,496] <wrn> rs: logz_example_rs: Buzz
[00:00:12.402,557] <err> rs: logz_example_rs: Fizzle
[00:00:12.402,618] <inf> rs: logz_example_rs: A: 0x306090c0 B: 0x1020304 C: 0x316293c4
[00:00:12.652,313] <inf> blinky: LED: 1
[00:00:12.652,343] <inf> blinky: A: 316293c4 B:  1020304, C: 326496c8
[00:00:12.652,404] <dbg> rs: log_dbg: logz_example_rs: Foo
[00:00:12.652,435] <dbg> rs: log_dbg: logz_example_rs: Bar
[00:00:12.652,465] <inf> rs: logz_example_rs: Fizz
[00:00:12.652,526] <wrn> rs: logz_example_rs: Buzz
[00:00:12.652,557] <err> rs: logz_example_rs: Fizzle
```