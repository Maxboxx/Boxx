#pragma once

#include "Types.h"
#include "Token.h"
#include "Regex.h"
#include "List.h"
#include "Array.h"
#include "Error.h"

///N Lexer

namespace Boxx {

	///B Lexer
	/// Used to get all tokens from a string
	class Lexer {
	public:
		///T Lex
		/// Get all from tokens from a code string
		///A const List<TokenPattern<T>>& patterns: A list of token patterns to search for
		///A const String& code: The code to lex
		///E LexerError: Thrown if the string contains an undefined token
		///M
		template <class T>
		static List<Token<T>> Lex(const List<TokenPattern<T>>& patterns, const String& code);
		///M
		
	private:
		static UInt Lines(const String& str) {
			UInt lines = 0;

			for (const char c : str) {
				if (c == '\n') lines++;
			}

			return lines;
		}
	};

	///B LexerError
	/// Thrown if the lexer can not lex a string
	class LexerError : public Error {
	public:
		LexerError() : Error() {}
		LexerError(const char* const msg) : Error(msg) {}
	};

	template <class T>
	static List<Token<T>> Lexer::Lex(const List<TokenPattern<T>>& patterns, const String& code) {
		static Regex whiteSpace = Regex("^%n*");
		static Regex undefinedToken = Regex("^~%n*");

		if (code.Size() == 0) return List<Token<T>>();

		String match = whiteSpace.Match(code)[0];
		UInt line = 1 + Lines(match);
		UInt i = match.Size();
		List<Token<T>> tokens;

		while (i < code.Size()) {
			bool found = false;

			for (const TokenPattern<T>& pattern : patterns) {
				Array<String> match = pattern.pattern.Match(code, i);

				if (!match.IsEmpty()) {
					i += match[0].Size();

					if (!pattern.ignore) {
						tokens.Add(Token<T>(pattern.type, match.Size() > 1 ? match[1] : match[0], line));
					}

					line += Lines(match[0]);

					found = true;
					break;
				}
			}

			if (!found) {
				Array<String> match = undefinedToken.Match(code, i);

				if (!match.IsEmpty()) {
					throw LexerError("Undefined token '" + match[0] + "'");
				}
			}

			if (i < code.Size()) {
				const String match = whiteSpace.Match(code, i)[0];
				i += match.Size();
				line += Lines(match);
			}
		}

		return tokens;
	}
}