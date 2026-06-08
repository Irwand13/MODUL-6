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

## Pertanyaan Demo

1. Apa itu race condition?
2. Mengapa output race berbeda-beda?
3. Apa fungsi mutex?
4. Mengapa mutex menghasilkan output yang benar?
5. Mengapa mutex lebih lambat?
6. Apa fungsi pthread_create()?
7. Apa fungsi pthread_join()?
8. Apa fungsi ps -T?
9. Apa fungsi htop?
10. Apa yang terjadi jika lupa pthread_mutex_unlock()?