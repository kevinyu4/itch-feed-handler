# itch-feed-handler

C++23 Nasdaq TotalView-ITCH 5.0 feed handler: MoldUDP64 replay and receive, decode, normalize, order book. See `README.md` for architecture and layout, and `docs/format.md` for the internal event format (the format is a hand-written spec; do not change it without being asked).

## Coding rules

- C++23. Fixed-width integers (`uint32_t`, `int64_t`, ...) for every wire field.
- No heap allocation and no exceptions on the hot path (receive, decode, normalize, book update). Report errors with `std::expected`. Pre-size containers at startup; index per-instrument state by locate code in flat arrays.
- Read wire bytes with `std::memcpy` or `std::bit_cast` plus `std::byteswap`. Never cast a byte pointer to a struct pointer.
- Prices are fixed-point integers end to end. Never use `float` or `double` for prices.
- Every decoder has unit tests built from hand-written byte arrays, including truncated and unknown messages.
- Performance changes come with a benchmark result (before and after, in percentiles) in the PR.

## Workflow

- Plan before code: propose an implementation plan and wait for approval before writing it.
- Write tests first and get them approved before the implementation.
- Keep each change under about 300 lines of diff. If it is growing larger, stop and propose a split.
- Prefer the smallest change that meets the spec. Do not add features, abstractions, or options that were not asked for.
- Conventional commit messages: `<type>(<scope>): <imperative summary>`.
  - Types: `feat`, `fix`, `test`, `perf`, `refactor`, `docs`, `build`, `ci`, `chore`.
  - Scope is required for any change under `src/`, `tools/`, `tests/`, `bench/` or `fuzz/`, and names the component: `itch`, `net`, `normalize`, `book`, `tools`, `bench`, `fuzz`. Repo-wide `docs`, `build` and `ci` changes may omit it.
  - Subject at most 72 characters, lowercase after the colon, no trailing period.
  - Body explains why the change is needed and why this approach, in short prose paragraphs wrapped at 72 columns. Do not list the files changed; the diff shows that.
  - `perf` commits include before/after benchmark numbers in the body.
- Code must pass CI locally before a PR: build, tests, ASan/UBSan build, clang-tidy, clang-format.

## Data

ITCH sample files live in `data/` (gitignored, multi-GB). Use a 100,000-message slice for day-to-day tests; run the full day only for nightly or explicit checks.
