#include <cstdio>
#include <string>

#include <benchmark/benchmark.h>
#include <strtox/strtox.h>

static void bm_strtox(benchmark::State& state) {
  std::string x = "1212.3e-12";

  while (state.KeepRunning())
  {
    benchmark::DoNotOptimize(strtox::parse_float(x));
  }
}
BENCHMARK(bm_strtox);

static void bm_stof(benchmark::State& state) {
  std::string x = "1212.3e-12";

  while (state.KeepRunning())
  {
    benchmark::DoNotOptimize(std::stof(x));
  }
}
BENCHMARK(bm_stof);

static void bm_sscanf(benchmark::State& state) {
  std::string x = "1212.3e-12";

  while (state.KeepRunning())
  {
    float f;
    benchmark::DoNotOptimize(sscanf(x.c_str(), "%f", &f));
  }
}
BENCHMARK(bm_sscanf);

BENCHMARK_MAIN();
