#include <cstdio>
#include <string>

#include <benchmark/benchmark.h>
#include <strtox/strtox.h>

static void bm_strtox(benchmark::State& state) {
  std::string x = "1212.39999999";

  while (state.KeepRunning())
  {
    benchmark::DoNotOptimize(strtox::parse_double(x));
  }
}
BENCHMARK(bm_strtox);

static void bm_stof(benchmark::State& state) {
  std::string x = "1212.39999999";

  while (state.KeepRunning())
  {
    benchmark::DoNotOptimize(std::stod(x));
  }
}
BENCHMARK(bm_stof);

static void bm_sscanf(benchmark::State& state) {
  std::string x = "1212.39999999";

  while (state.KeepRunning())
  {
    double f;
    benchmark::DoNotOptimize(sscanf(x.c_str(), "%lf", &f));
  }
}
BENCHMARK(bm_sscanf);

BENCHMARK_MAIN();
