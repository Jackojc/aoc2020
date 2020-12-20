#include <string>
#include <cstdint>
#include <unordered_map>

#include <util.hpp>
#include <tinge.hpp>


#define BENCH

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>


// Lexer.
namespace jc {
	struct View {
		const char *begin, *end;
	};

	enum {
		TOKEN_NONE,
		TOKEN_EOF,
		TOKEN_LITERAL,
		TOKEN_ADD,
		TOKEN_MUL,
		TOKEN_LPAREN,
		TOKEN_RPAREN,
	};

	struct Token {
		View view;
		uint8_t type;
	};

	constexpr bool operator==(const Token& t, const uint8_t type) {
		return t.type == type;
	}

	constexpr bool operator!=(const Token& t, const uint8_t type) {
		return not(t == type);
	}



	inline Token next_token(const char*& ptr) {
		Token tok{{ptr, ptr + 1}, TOKEN_NONE};

		auto& [view, type] = tok;
		auto& [vbegin, vend] = view;

		if (*ptr == '\0') {
			type = TOKEN_EOF;
		}

		else if (*ptr >= '0' and *ptr <= '9') {
			type = TOKEN_LITERAL;
			vbegin = ptr;
			do { ++ptr; } while (*ptr >= '0' and *ptr <= '9');
			vend = ptr;
		}

		else if (*ptr == ' ' || *ptr == '\n') {
			do { ++ptr; } while (*ptr == ' ' or *ptr == '\n');
			return next_token(ptr);
		}

		else if (*ptr == '+') { type = TOKEN_ADD; ++ptr; }
		else if (*ptr == '*') { type = TOKEN_MUL; ++ptr; }

		else if (*ptr == '(') { type = TOKEN_LPAREN; ++ptr; }
		else if (*ptr == ')') { type = TOKEN_RPAREN; ++ptr; }

		return tok;
	}


	struct Context {
		const char* ptr;
		Token current {}, lookahead {};
	};

	inline Token next(Context& ctx) {
		ctx.current = ctx.lookahead;
		ctx.lookahead = next_token(ctx.ptr);
		return ctx.current;
	}
}





// Parser.
namespace jc {
	struct part1_tag;
	struct part2_tag;

	template <typename T>
	inline long expr(Context& ctx, int min = 0) {
		long res = 0;

		next(ctx);

		if (ctx.current == TOKEN_LPAREN) {
	 		res = expr<T>(ctx);
			next(ctx); // assume there is a closing paren
		}

		else if (ctx.current == TOKEN_LITERAL) {
			for (auto [it, end] = ctx.current.view; it != end; it++)
				res = (res * 10) + (*it - '0');
		}

		while (ctx.lookahead != TOKEN_EOF) {
			if (ctx.lookahead == TOKEN_ADD or ctx.lookahead == TOKEN_MUL) {
				const auto& [op, _] = ctx.lookahead.view;
				uint8_t prec = 1;

				if constexpr(std::is_same_v<T, part2_tag>) {
					prec = std::array{ 1, 2 } [*op - '*'];
				}

				if (prec < min)
					break;

				next(ctx);

				if (ctx.current == TOKEN_ADD)
					res += expr<T>(ctx, prec + 1);

				else if (ctx.current == TOKEN_MUL)
					res *= expr<T>(ctx, prec + 1);

				continue;
			}

			break;
		}

		return res;
	}
}



long part1(const char* ptr) {
	long sum = 0;
	jc::Context ctx {ptr};
	next(ctx);

	while (ctx.lookahead != jc::TOKEN_EOF)
		sum += jc::expr<jc::part1_tag>(ctx);

	return sum;
}

long part2(const char* ptr) {
	long sum = 0;
	jc::Context ctx{ptr};
	next(ctx);

	while (ctx.lookahead != jc::TOKEN_EOF)
		sum += jc::expr<jc::part2_tag>(ctx);

	return sum;
}


int main(int argc, const char* argv[]) {
	if (argc != 2) {
		tinge::errorln("usage: ./out <input>");
		return -1;
	}

	const auto str = util::read_file(argv[1]);


	#ifdef BENCH
		using namespace std::chrono_literals;
		auto bench = ankerl::nanobench::Bench().warmup(10).minEpochIterations(100).timeUnit(1us, "μs");

		bench.run("part1", [&] {
			ankerl::nanobench::doNotOptimizeAway(part1(str.c_str()));
		});

		bench.run("part2", [&] {
			ankerl::nanobench::doNotOptimizeAway(part2(str.c_str()));
		});
	#endif


	for (int i = 0; i < 1000; i++) {
		ankerl::nanobench::doNotOptimizeAway(part1(str.c_str()));
		ankerl::nanobench::doNotOptimizeAway(part2(str.c_str()));
	}

	return 0;
}
