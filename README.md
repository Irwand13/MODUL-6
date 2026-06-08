# Demo Modul 6 - Thread dan Mutex

## Compile

```bash
gcc counter_race.c -o counter_race -lpthread
gcc counter_mutex.c -o counter_mutex -lpthread
```

## Race Condition

Jalankan 3 kali:

```bash
./counter_race
./counter_race
./counter_race
```

Amati bahwa hasil bisa berbeda-beda.

## Lihat Thread

Jalankan:

```bash
./counter_race &
ps -T -p PID
```

atau:

```bash
htop
```

Tekan:

```text
H
```

## Mutex Validation

Jalankan:

```bash
./counter_mutex
./counter_mutex
./counter_mutex
```

Hasil harus selalu:

```text
FINAL = 200000
```

## Performance Test

```bash
time ./counter_race
time ./counter_mutex
```
