#ifndef _BOXX_MANGO_HEADER
#define _BOXX_MANGO_HEADER

#include "Types.h"
#include "List.h"
#include "Pair.h"
#include "Map.h"
#include "Set.h"
#include "String.h"
#include "Regex.h"
#include "Token.h"
#include "Lexer.h"
#include "Optional.h"
#include "Math.h"

///[Settings] block: indent

///[Namespace] Boxx
namespace Boxx {
	class Mango;

	///[Heading] Mango

	///[Title] MangoType
	/// Enum of all types of mango values.
	///[Block] MangoType
	enum class MangoType : UByte {
		/// Nil type.
		Nil,

		/// Boolean type.
		Boolean,

		/// Number type.
		Number,

		/// String type.
		String,

		/// List type.
		List,

		/// Map type.
		Map
	};

	///[Title] MangoList
	/// Typedef for Mango list.
	typedef List<Mango> MangoList;

	///[Title] MangoMap
	/// Typedef for Mango map.
	typedef Map<String, Mango> MangoMap;

	///[Title] Mango
	/// A mango data structure used for mango data.
	///[Block] Mango
	class Mango {
	public:
		///[Heading] Constructors

		/// Nil constructor.
		Mango();

		/// Creates a mango value of the specified type.
		explicit Mango(const MangoType type);

		/// Creates a boolean mango value.
		Mango(const bool boolean);

		/// Creates a mango number from int.
		Mango(const Int number);

		/// Creates a mango number from long.
		Mango(const Long number);

		/// Creates a mango number from float.
		Mango(const float number);

		/// Creates a mango number from double.
		Mango(const double number);

		/// Creates a mango string value.
		Mango(const String& string);

		/// Creates a mango list value.
		Mango(const MangoList& list);

		/// Creates a mango map value.
		Mango(const MangoMap& map);

		/// Creates a labeled mango value of the specified type.
		Mango(const String& label, const MangoType type);

		/// Creates a labeled boolean mango value.
		Mango(const String& label, const bool boolean);

		/// Creates a labeled mango number.
		Mango(const String& label, const Int number);

		/// Creates a labeled mango number.
		Mango(const String& label, const Long number);

		/// Creates a labeled mango number.
		Mango(const String& label, const float number);

		/// Creates a labeled mango number.
		Mango(const String& label, const double number);

		/// Creates a labeled mango string.
		Mango(const String& label, const String& string);

		/// Creates a labeled mango list.
		Mango(const String& label, const MangoList& list);

		/// Creates a labeled mango map.
		Mango(const String& label, const MangoMap& map);

		Mango(const Mango& mango);
		Mango(Mango&& mango) noexcept;
		~Mango();

		///[Heading] Methods

		/// Get the type of the mango value.
		MangoType Type() const;

		/// Setd the label of the mango value.
		/// An empty string will remove the label.
		void SetLabel(const String& label);

		/// Gets the label for this mango value.
		/// If the mango value has no label an empty string is returned.
		String GetLabel() const;

		/// Adds a mango value to the mango list.
		///[Error] MangoTypeError: Thrown if the mango type is not list.
		void Add(const Mango& mango);

		/// Adds a new key to the mango map.
		///[Error] MangoTypeError: Thrown if the mango type is not map.
		void Add(const String& key, const Mango& mango);

		/// Returns the size of the mango list.
		///[Error] MangoTypeError: Thrown if the mango type is not list.
		UInt Length() const;

		/// Copies the mango value.
		Mango Copy() const;

		///[Heading] Operators

		/// Returns the boolean mango value.
		///[Error] MangoTypeError: Thrown if the mango type is not boolean.
		operator bool() const;

		/// Returns the mango number.
		///[Error] MangoTypeError: Thrown if the mango type is not number.
		operator Int() const;

		/// Returns the mango number.
		///[Error] MangoTypeError: Thrown if the mango type is not number.
		operator Long() const;

		/// Returns the mango number.
		///[Error] MangoTypeError: Thrown if the mango type is not number.
		operator float() const;

		/// Returns the mango number.
		///[Error] MangoTypeError: Thrown if the mango type is not number.
		operator double() const;

		/// Returns the mango string.
		///[Error] MangoTypeError: Thrown if the mango type is not string.
		operator String() const;

		/// Returns the mango list.
		///[Error] MangoTypeError: Thrown if the mango type is not list.
		operator MangoList() const;

		/// Returns the mango map.
		///[Error] MangoTypeError: Thrown if the mango type is not map.
		operator MangoMap() const;

		/// Gets or sets a value in the mango list.
		///[Error] MangoTypeError: Thrown if the mango type is not list.
		///M
		Mango& operator[](const UInt index);
		const Mango& operator[](const UInt index) const;
		///M

		/// Gets or sets a value in the mango map.
		///[Error] MangoTypeError: Thrown if the mango type is not map.
		///[Error] MangoKeyError: Thrown if the key does not exist.
		///M
		Mango& operator[](const String& key);
		const Mango& operator[](const String& key) const;
		Mango& operator[](const char* const key);
		const Mango& operator[](const char* const key) const;
		///M

		/// Assigns a boolean value to the mango value.
		/// The mango type is changed to boolean.
		void operator=(const bool boolean);

		/// Assigns a number to the mango value.
		/// The mango type is changed to number.
		void operator=(const Int number);

		/// Assigns a number to the mango value.
		/// The mango type is changed to number.
		void operator=(const Long number);

		/// Assigns a number to the mango value.
		/// The mango type is changed to number.
		void operator=(const float number);

		/// Assigns a number to the mango value.
		/// The mango type is changed to number.
		void operator=(const double number);

		/// Assigns a string to the mango value.
		/// The mango type is changed to string.
		void operator=(const String& string);

		/// Assigns a list to the mango value.
		/// The mango type is changed to list.
		void operator=(const MangoList& list);

		/// Assigns a map to the mango value.
		/// The mango type is changed to map.
		void operator=(const MangoMap& map);

		void operator=(const Mango& mango);
		void operator=(Mango&& mango) noexcept;

		/// Checks the equality of two mango values.
		///M
		bool operator==(const Mango& mango) const;
		bool operator!=(const Mango& mango) const;
		///M

		///[Heading] Static functions

		/// Encodes the mango value to a string.
		///[Arg] pretty: Creates a pretty string if {true}.
		static String Encode(const Mango& mango, const bool pretty = false);

		/// Decodes a string to a mango value.
		///[Error] MangoDecodeError: Thrown if the mango string can not be decoded.
		static Mango Decode(const String& mango);

	private:
		static String EncodeNode(const Mango& mango);
		static String EncodeNode(const Mango& mango, const String& tabs);

		enum class InternalType : UByte {
			Default,
			Integer,
			Var
		};

		MangoType type;
		InternalType internalType = InternalType::Default;
		String label;
		bool boolean = false;
		double number = 0.0;
		String string;
		MangoList list;
		MangoMap map;

		enum class TokenType : UByte {
			None,
			Comment,
			Name,
			Var,
			VarUnpack,
			Template,
			TemplateUnpack,
			Boolean,
			Nil,
			Number,
			String,
			Colon,
			Assign,
			OpenCurl,
			CloseCurl,
			OpenSq,
			CloseSq
		};

		struct Template;

		struct ParsingInfo {
			MangoMap variables;
			Map<String, Template> templates;

			ParsingInfo Copy() const;
		};

		static Mango Parse(TokenList<TokenType>& tokens);

		static Optional<Mango> ParseNil(TokenList<TokenType>& tokens, ParsingInfo& info);
		static Optional<Mango> ParseBoolean(TokenList<TokenType>& tokens, ParsingInfo& info);
		static Optional<Mango> ParseNumber(TokenList<TokenType>& tokens, ParsingInfo& info);
		static Optional<Mango> ParseString(TokenList<TokenType>& tokens, ParsingInfo& info);
		static Optional<Mango> ParseVariable(TokenList<TokenType>& tokens, ParsingInfo& info, bool unpack = false);
		static Optional<Mango> ParseTemplate(TokenList<TokenType>& tokens, ParsingInfo& info, bool unpack = false);
		static void InsertTemplateValues(Mango& mango, const Map<String, Mango>& vars);

		static MangoList ParseListItems(TokenList<TokenType>& tokens, ParsingInfo& info);
		static Optional<Mango> ParseList(TokenList<TokenType>& tokens, ParsingInfo& info);

		static Optional<Pair<String, Mango>> ParseMapItem(TokenList<TokenType>& tokens, ParsingInfo& info);
		static MangoMap ParseMapItems(TokenList<TokenType>& tokens, ParsingInfo& info);
		static Optional<Mango> ParseMap(TokenList<TokenType>& tokens, ParsingInfo& info);

		static Optional<String> ParseRawString(TokenList<TokenType>& tokens, ParsingInfo& info);
		static Optional<String> ParseName(TokenList<TokenType>& tokens, ParsingInfo& info);
		static Optional<String> ParseLabel(TokenList<TokenType>& tokens, ParsingInfo& info);
		static Optional<Mango> ParseValue(TokenList<TokenType>& tokens, ParsingInfo& info, const bool allowInnerLabels = false);
		static Optional<Mango> ParseLabeledValue(TokenList<TokenType>& tokens, ParsingInfo& info, const bool forceLabel = false);

		static bool ParseVariableAssignment(TokenList<TokenType>& tokens, ParsingInfo& info, const bool isList);
		static bool ParseTemplateAssignment(TokenList<TokenType>& tokens, ParsingInfo& info, const bool isList);
	};

	struct Mango::Template  {
		List<String> vars;
		Mango content;
	};

	inline Mango::ParsingInfo Mango::ParsingInfo::Copy() const {
		ParsingInfo info;

		for (const Pair<String, Mango>& pair : variables) {
			info.variables.Add(pair.key, pair.value.Copy());
		}

		for (const Pair<String, Template>& pair : templates) {
			info.templates.Add(pair);
		}

		return info;
	}

	///[Title] MangoError
	/// Base class for all mango errors.
	///[Block] MangoError: Error
	class MangoError : public Error {
	public:
		MangoError() : Error() {}
		MangoError(const char* const msg) : Error(msg) {}

		virtual String Name() const override {
			return "MangoError";
		}
	};

	///[Title] MangoTypeError
	/// Used for type related mango errors.
	///[Block] MangoTypeError: MangoError
	class MangoTypeError : public MangoError {
	public:
		MangoTypeError() : MangoError() {}
		MangoTypeError(const char* const msg) : MangoError(msg) {}

		virtual String Name() const override {
			return "MangoTypeError";
		}
	};

	///[Title] MangoKeyError
	/// Used for map key related errors.
	///[Block] MangoKeyError: MangoError
	class MangoKeyError : public MangoError {
	public:
		MangoKeyError() : MangoError() {}
		MangoKeyError(const char* const msg) : MangoError(msg) {}

		virtual String Name() const override {
			return "MangoKeyError";
		}
	};

	///[Title] MangoDecodeError
	/// Used for decoding errors.
	///[Block] MangoDecodeError: MangoError
	class MangoDecodeError : public MangoError {
	public:
		MangoDecodeError() : MangoError() {}
		MangoDecodeError(const char* const msg) : MangoError(msg) {}

		virtual String Name() const override {
			return "MangoDecodeError";
		}
	};

	inline Mango::Mango() {
		type = MangoType::Nil;
	}

	inline Mango::Mango(const MangoType type) {
		this->type = type;
	}

	inline Mango::Mango(const bool boolean) {
		type = MangoType::Boolean;
		this->boolean = boolean;
	}

	inline Mango::Mango(const Int number) {
		type = MangoType::Number;
		internalType = InternalType::Integer;
		this->number = number;
	}

	inline Mango::Mango(const Long number) {
		type = MangoType::Number;
		internalType = InternalType::Integer;
		this->number = (double)number;
	}

	inline Mango::Mango(const float number) {
		type = MangoType::Number;
		internalType = InternalType::Integer;
		this->number = number;
	}

	inline Mango::Mango(const double number) {
		type = MangoType::Number;
		internalType = InternalType::Integer;
		this->number = number;
	}

	inline Mango::Mango(const String& string) {
		type = MangoType::String;
		this->string = string;
	}

	inline Mango::Mango(const MangoList& list) {
		type = MangoType::List;
		this->list = list;
	}

	inline Mango::Mango(const MangoMap& map) {
		type = MangoType::Map;
		this->map = map;
	}

	inline Mango::Mango(const String& label, const MangoType type) {
		this->type = type;
		this->label = label;
	}

	inline Mango::Mango(const String& label, const bool boolean) {
		type = MangoType::Boolean;
		this->boolean = boolean;
		this->label = label;
	}

	inline Mango::Mango(const String& label, const Int number) {
		type = MangoType::Number;
		internalType = InternalType::Integer;
		this->number = number;
		this->label = label;
	}

	inline Mango::Mango(const String& label, const Long number) {
		type = MangoType::Number;
		internalType = InternalType::Integer;
		this->number = (double)number;
		this->label = label;
	}

	inline Mango::Mango(const String& label, const float number) {
		type = MangoType::Number;
		internalType = InternalType::Default;
		this->number = number;
		this->label = label;
	}

	inline Mango::Mango(const String& label, const double number) {
		type = MangoType::Number;
		internalType = InternalType::Default;
		this->number = number;
		this->label = label;
	}

	inline Mango::Mango(const String& label, const String& string) {
		type = MangoType::String;
		this->string = string;
		this->label = label;
	}

	inline Mango::Mango(const String& label, const MangoList& list) {
		type = MangoType::List;
		this->list = list;
		this->label = label;
	}

	inline Mango::Mango(const String& label, const MangoMap& map) {
		type = MangoType::Map;
		this->map = map;
		this->label = label;
	}

	inline Mango::Mango(const Mango& mango) {
		type = mango.type;
		label = mango.label;
		internalType = mango.internalType;

		switch (type) {
			case MangoType::Nil: break;
			case MangoType::Boolean: boolean = mango.boolean; break;
			case MangoType::Number: number = mango.number;  break;
			case MangoType::String: string = mango.string; break;
			case MangoType::List: list = mango.list; break;
			case MangoType::Map: map = mango.map; break;
		}
	}

	inline Mango::Mango(Mango&& mango) noexcept {
		type = mango.type;
		label = std::move(mango.label);
		internalType = mango.internalType;

		switch (type) {
			case MangoType::Nil: break;
			case MangoType::Boolean: boolean = mango.boolean; break;
			case MangoType::Number: number = mango.number; break;
			case MangoType::String: string = std::move(mango.string); break;
			case MangoType::List: list = std::move(mango.list); break;
			case MangoType::Map: map = std::move(mango.map); break;
		}
	}

	inline Mango::~Mango() {

	}

	inline MangoType Mango::Type() const {
		return type;
	}

	inline void Mango::SetLabel(const String& label) {
		this->label = label;
	}

	inline String Mango::GetLabel() const {
		return label;
	}

	inline void Mango::Add(const Mango& mango) {
		if (type != MangoType::List) throw MangoTypeError("Type is not list");
		list.Add(mango);
	}

	inline void Mango::Add(const String& key, const Mango& mango) {
		if (type != MangoType::Map) throw MangoTypeError("Type is not map");

		try {
			map.Add(key, mango);
		}
		catch (MapKeyError) {
			throw MangoKeyError("Key already exists");
		}
	}

	inline UInt Mango::Length() const {
		if (type != MangoType::List) throw MangoTypeError("Type is not list");
		return list.Count();
	}

	inline Mango Mango::Copy() const {
		switch (type) {
			case MangoType::Nil: {
				Mango m = Mango(label, MangoType::Nil);
				m.internalType = internalType;
				return m;
			}

			case MangoType::Boolean: {
				Mango m = Mango(label, boolean);
				m.internalType = internalType;
				return m;
			}

			case MangoType::Number: {
				Mango m = Mango(label, number);
				m.internalType = internalType;
				return m;
			}

			case MangoType::String: {
				Mango m = Mango(label, string);
				m.internalType = internalType;
				return m;
			}

			case MangoType::List: {
				MangoList list;

				for (const Mango& mango : this->list) {
					list.Add(mango.Copy());
				}

				Mango m = Mango(label, list);
				m.internalType = internalType;
				return m;
			}

			case MangoType::Map: {
				MangoMap map;

				for (const Pair<String, Mango>& pair : this->map) {
					map.Add(pair.key, pair.value.Copy());
				}

				Mango m = Mango(label, map);
				m.internalType = internalType;
				return m;
			}
		}

		return Mango(MangoType::Nil);
	}

	inline Mango::operator bool() const {
		if (type != MangoType::Boolean) throw MangoTypeError("Type is not boolean");
		return boolean;
	}

	inline Mango::operator Int() const {
		if (type != MangoType::Number) throw MangoTypeError("Type is not number");
		return (Int)number;
	}

	inline Mango::operator Long() const {
		if (type != MangoType::Number) throw MangoTypeError("Type is not number");
		return (Long)number;
	}

	inline Mango::operator float() const {
		if (type != MangoType::Number) throw MangoTypeError("Type is not number");
		return (float)number;
	}

	inline Mango::operator double() const {
		if (type != MangoType::Number) throw MangoTypeError("Type is not number");
		return number;
	}

	inline Mango::operator String() const {
		if (type != MangoType::String) throw MangoTypeError("Type is not string");
		return string;
	}

	inline Mango::operator MangoList() const {
		if (type != MangoType::List) throw MangoTypeError("Type is not list");
		return list;
	}

	inline Mango::operator MangoMap() const {
		if (type != MangoType::Map) throw MangoTypeError("Type is not map");
		return map;
	}

	inline Mango& Mango::operator[](const UInt index) {
		if (type != MangoType::List) throw MangoTypeError("Type is not list");
		return list[index];
	}

	inline const Mango& Mango::operator[](const UInt index) const {
		if (type != MangoType::List) throw MangoTypeError("Type is not list");
		return list[index];
	}

	inline Mango& Mango::operator[](const String& key) {
		if (type != MangoType::Map) throw MangoTypeError("Type is not map");

		try {
			return map[key];
		}
		catch (MapKeyError) {
			throw MangoKeyError("Key '" + key + "' not found");
		}
	}

	inline const Mango& Mango::operator[](const String& key) const {
		if (type != MangoType::Map) throw MangoTypeError("Type is not map");
		
		try {
			return map[key];
		}
		catch (MapKeyError) {
			throw MangoKeyError("Key '" + key + "' not found");
		}
	}

	inline Mango& Mango::operator[](const char* const key) {
		if (type != MangoType::Map) throw MangoTypeError("Type is not map");

		try {
			return map[key];
		}
		catch (MapKeyError) {
			throw MangoKeyError("Key '" + String(key) + "' not found");
		}
	}

	inline const Mango& Mango::operator[](const char* const key) const {
		if (type != MangoType::Map) throw MangoTypeError("Type is not map");

		try {
			return map[key];
		}
		catch (MapKeyError) {
			throw MangoKeyError("Key '" + String(key) + "' not found");
		}
	}

	inline void Mango::operator=(const bool boolean) {
		type = MangoType::Boolean;
		this->boolean = boolean;
	}

	inline void Mango::operator=(const Int number) {
		type = MangoType::Number;
		internalType = InternalType::Integer;
		this->number = number;
	}

	inline void Mango::operator=(const Long number) {
		type = MangoType::Number;
		internalType = InternalType::Integer;
		this->number = (double)number;
	}

	inline void Mango::operator=(const float number) {
		type = MangoType::Number;
		internalType = InternalType::Default;
		this->number = number;
	}

	inline void Mango::operator=(const double number) {
		type = MangoType::Number;
		internalType = InternalType::Default;
		this->number = number;
	}

	inline void Mango::operator=(const String& string) {
		type = MangoType::String;
		this->string = string;
	}

	inline void Mango::operator=(const MangoList& list) {
		type = MangoType::List;
		this->list = list;
	}

	inline void Mango::operator=(const MangoMap& map) {
		type = MangoType::Map;
		this->map = map;
	}

	inline void Mango::operator=(const Mango& mango) {
		type = mango.type;
		label = mango.label;
		internalType = mango.internalType;

		switch (type) {
			case MangoType::Nil: break;
			case MangoType::Boolean: boolean = mango.boolean; break;
			case MangoType::Number: number = mango.number; break;
			case MangoType::String: string = mango.string; break;
			case MangoType::List: list = mango.list; break;
			case MangoType::Map: map = mango.map; break;
		}
	}

	inline void Mango::operator=(Mango&& mango) noexcept {
		type = mango.type;
		label = mango.label;
		internalType = mango.internalType;

		switch (type) {
			case MangoType::Nil: break;
			case MangoType::Boolean: boolean = mango.boolean; break;
			case MangoType::Number: number = mango.number; break;
			case MangoType::String: string = std::move(mango.string); break;
			case MangoType::List: list = std::move(mango.list); break;
			case MangoType::Map: map = std::move(mango.map); break;
		}
	}
	
	inline bool Mango::operator==(const Mango& mango) const {
		if (type != mango.type) return false;

		switch (type) {
			case MangoType::Nil: return true;
			case MangoType::Boolean: return boolean == mango.boolean;
			case MangoType::Number: return number == mango.number;
			case MangoType::String: return string == mango.string;
			case MangoType::List: return list == mango.list;
			case MangoType::Map: return map == mango.map;
		}
	}

	inline bool Mango::operator!=(const Mango& mango) const {
		return !operator==(mango);
	}

	inline String Mango::Encode(const Mango& mango, const bool pretty) {
		if (pretty)
			return EncodeNode(mango, "");
		else
			return EncodeNode(mango);
	}

	inline String Mango::EncodeNode(const Mango& mango) {
		static Regex labelPattern = Regex("^%w+$");

		String str = "";

		if (mango.label.Length() > 0) {
			if (labelPattern.Match(mango.label))
				str += mango.label + ":";
			else
				str += "\"" + mango.label.Escape() + "\":";
		}

		switch (mango.type) {
			case MangoType::Nil: {
				str += "nil";
				break;
			}
			case MangoType::Boolean: {
				str += mango.boolean ? "true" : "false";
				break;
			}
			case MangoType::Number: {
				if (mango.internalType == InternalType::Integer)
					str += String::ToString((Long)mango.number);
				else
					str += String::ToString(mango.number);
				break;
			}
			case MangoType::String: {
				str += "\"" + mango.string.Escape() + "\"";
				break;
			}
			case MangoType::List: {
				str += "[";

				for (const Mango& m : mango.list)
					str += EncodeNode(m) + " ";

				str = str.Sub(0, str.Length() - 2) + "]";
				break;
			}
			case MangoType::Map: {
				str += "{";

				for (const Pair<String, Mango>& m : mango.map) {
					if (labelPattern.Match(m.key))
						str += m.key + ":";
					else
						str += "\"" + m.key.Escape() + "\":";

					str += EncodeNode(m.value) + " ";
				}

				str = str.Sub(0, str.Length() - 2) + "}";
				break;
			}
		}

		return str;
	}

	inline String Mango::EncodeNode(const Mango& mango, const String& tabs) {
		static Regex labelPattern = Regex("^%w+$");

		const String nextTabs = tabs + "\t";
		String str = "";

		if (mango.label.Length() > 0) {
			if (labelPattern.Match(mango.label))
				str += mango.label + ": ";
			else
				str += "\"" + mango.label.Escape() + "\": ";
		}

		switch (mango.type) {
			case MangoType::Nil: {
				str += "nil";
				break;
			}
			case MangoType::Boolean: {
				str += mango.boolean ? "true" : "false";
				break;
			}
			case MangoType::Number: {
				if (mango.internalType == InternalType::Integer)
					str += String::ToString((Long)mango.number);
				else
					str += String::ToString(mango.number);
				break;
			}
			case MangoType::String: {
				str += "\"" + mango.string.Escape() + "\"";
				break;
			}
			case MangoType::List: {
				str += "[\n";

				for (const Mango& m : mango.list)
					str += nextTabs + EncodeNode(m, nextTabs);

				str += tabs + "]";
				break;
			}
			case MangoType::Map: {
				str += "{\n";

				for (const Pair<String, Mango>& m : mango.map) {
					if (labelPattern.Match(m.key))
						str += nextTabs + m.key;
					else
						str += nextTabs + "\"" + m.key.Escape() + "\"";

					if (m.value.label.Length() == 0) {
						str += ": ";
					}
					else {
						str += " ";
					}

					str += EncodeNode(m.value, nextTabs);
				}

				str += tabs + "}";
				break;
			}
		}

		return str + "\n";
	}

	inline Mango Mango::Decode(const String& mango) {
		List<TokenPattern<TokenType>> patterns;
		patterns.Add(TokenPattern<TokenType>(TokenType::Comment, "%-%-#{%/+}~{%0%-}*%0%-%-", true, true));
		patterns.Add(TokenPattern<TokenType>(TokenType::Comment, "%-%-~\n*", true, true));

		patterns.Add(TokenPattern<TokenType>(TokenType::Boolean, "true|false"));
		patterns.Add(TokenPattern<TokenType>(TokenType::Nil, "nil"));
		patterns.Add(TokenPattern<TokenType>(TokenType::Number, "%d*%.?%d+"));
		patterns.Add(TokenPattern<TokenType>(TokenType::Name, "%w+"));
		patterns.Add(TokenPattern<TokenType>(TokenType::String, "\"()\"", true));
		patterns.Add(TokenPattern<TokenType>(TokenType::String, "\"(\\\\)\"", true));
		patterns.Add(TokenPattern<TokenType>(TokenType::String, "\"(./~{{\\\\}*\\})\"", true));

		patterns.Add(TokenPattern<TokenType>(TokenType::TemplateUnpack, "%#%#(%w+)"));
		patterns.Add(TokenPattern<TokenType>(TokenType::Template, "%#(%w+)"));
		patterns.Add(TokenPattern<TokenType>(TokenType::VarUnpack, "%$%$(%w+)"));
		patterns.Add(TokenPattern<TokenType>(TokenType::Var, "%$(%w+)"));

		patterns.Add(TokenPattern<TokenType>(TokenType::Assign, "%=", true));
		patterns.Add(TokenPattern<TokenType>(TokenType::Colon, "%:", true));
		patterns.Add(TokenPattern<TokenType>(TokenType::OpenCurl, "%{", true));
		patterns.Add(TokenPattern<TokenType>(TokenType::CloseCurl, "%}", true));
		patterns.Add(TokenPattern<TokenType>(TokenType::OpenSq, "%[", true));
		patterns.Add(TokenPattern<TokenType>(TokenType::CloseSq, "%]", true));

		try {
			TokenList<TokenType> tokens = Lexer::Lex(patterns, mango);
			return Parse(tokens);
		}
		catch (MangoDecodeError& e) {
			throw e;
		}
		catch (TokenListError& e) {
			throw MangoDecodeError("Unexpected end of string");
		}
		catch (LexerError& e) {
			throw MangoDecodeError(e.Message());
		}
	}

	inline Mango Mango::Parse(TokenList<TokenType>& tokens) {
		UInt index = 0;

		ParsingInfo info;

		Optional<Mango> mango = ParseLabeledValue(tokens, info);

		if (!tokens.AtEnd()) throw MangoDecodeError("Unexpected token: '" + tokens.Current().rawValue + "'");

		if (mango) {
			return *mango;
		}
		else {
			throw MangoDecodeError("Invalid mango value");
		}
	}

	inline Optional<Mango> Mango::ParseNil(TokenList<TokenType>& tokens, ParsingInfo& info) {
		if (tokens.Current().type == TokenType::Nil) {
			tokens.Advance();
			return Mango(MangoType::Nil);
		}

		return nullptr;
	}

	inline Optional<Mango> Mango::ParseBoolean(TokenList<TokenType>& tokens, ParsingInfo& info) {
		if (tokens.Current().type == TokenType::Boolean) {
			tokens.Advance();
			return Mango(tokens.PeekPrevious().value == "true");
		}

		return nullptr;
	}

	inline Optional<Mango> Mango::ParseNumber(TokenList<TokenType>& tokens, ParsingInfo& info) {
		if (tokens.Current().type == TokenType::Number) {
			tokens.Advance();
			return Mango(tokens.PeekPrevious().value.ToDouble());
		}

		return nullptr;
	}

	inline Optional<Mango> Mango::ParseString(TokenList<TokenType>& tokens, ParsingInfo& info) {
		if (Optional<String> str = ParseRawString(tokens, info)) {
			return Mango(*str);
		}

		return nullptr;
	}

	inline Optional<Mango> Mango::ParseVariable(TokenList<TokenType>& tokens, ParsingInfo& info, bool unpack) {
		if (tokens.Current().type == (unpack ? TokenType::VarUnpack : TokenType::Var)) {
			tokens.Advance();
			Mango m;

			if (info.variables.Contains(tokens.PeekPrevious().value, m)) {
				return m.Copy();
			}
			else {
				return Mango(MangoType::Nil);
			}
		}

		return nullptr;
	}

	inline Optional<Mango> Mango::ParseTemplate(TokenList<TokenType>& tokens, ParsingInfo& info, bool unpack) {
		if (tokens.Current().type == (unpack ? TokenType::TemplateUnpack : TokenType::Template)) {
			const String name = tokens.Current().value;
			tokens.Advance();

			if (tokens.Current().type != TokenType::OpenSq) {
				throw MangoDecodeError("'[' expected to open template variable list");
			}

			tokens.Advance();

			List<Mango> values;

			while (Optional<Mango> value = ParseLabeledValue(tokens, info)) {
				values.Add(*value);
			}

			if (tokens.Current().type != TokenType::CloseSq) {
				throw MangoDecodeError("']' expected to close template variable list");
			}

			tokens.Advance();

			Template t;

			if (!info.templates.Contains(name, t)) {
				return Mango(MangoType::Nil);
			}

			Map<String, Mango> vars;

			UInt size = Math::Min(values.Count(), t.vars.Count());

			for (UInt i = 0; i < size; i++) {
				vars.Add(t.vars[i], values[i]);
			}

			Mango mango = t.content.Copy();
			InsertTemplateValues(mango, vars);
			return mango;
		}

		return nullptr;
	}

	inline void Mango::InsertTemplateValues(Mango& mango, const Map<String, Mango>& vars) {
		switch (mango.type) {
			case MangoType::List: {
				for (Mango& m : mango.list) {
					InsertTemplateValues(m, vars);
				}

				break;
			}

			case MangoType::Map: {
				for (Pair<String, Mango>& pair : mango.map) {
					InsertTemplateValues(pair.value, vars);
				}

				break;
			}

			case MangoType::String: {
				if (mango.internalType != InternalType::Var) break;

				Mango var;

				if (vars.Contains(mango.string, var)) {
					mango = var.Copy();
				}
				else {
					mango = Mango(MangoType::Nil);
				}

				break;
			}
		}
	}

	inline MangoList Mango::ParseListItems(TokenList<TokenType>& tokens, ParsingInfo& info) {
		ParsingInfo parseInfo = info.Copy();
		MangoList list;

		while (ParseVariableAssignment(tokens, parseInfo, false) || ParseTemplateAssignment(tokens, parseInfo, false));

		while (Optional<Mango> item = ParseLabeledValue(tokens, parseInfo)) {
			list.Add(*item);
		}

		return list;
	}

	inline Optional<Mango> Mango::ParseList(TokenList<TokenType>& tokens, ParsingInfo& info) {
		if (tokens.Current().type != TokenType::OpenSq) return nullptr;
		tokens.Advance();

		MangoList list = ParseListItems(tokens, info);

		if (tokens.Current().type != TokenType::CloseSq) {
			throw MangoDecodeError("']' expected");	
		}

		tokens.Advance();
		return Mango(list);
	}

	inline Optional<Pair<String, Mango>> Mango::ParseMapItem(TokenList<TokenType>& tokens, ParsingInfo& info) {
		if (Optional<String> key = ParseName(tokens, info)) {
			Optional<Mango> value = nullptr;

			if (tokens.Current().type == TokenType::Colon) {
				tokens.Advance();
				value = ParseValue(tokens, info, true);
			}
			else {
				value = ParseLabeledValue(tokens, info, true);
			}

			if (!value) {
				throw MangoDecodeError("Value expected after map key");
			}

			return Pair<String, Mango>(*key, *value);
		}

		return nullptr;
	}

	inline MangoMap Mango::ParseMapItems(TokenList<TokenType>& tokens, ParsingInfo& info) {
		ParsingInfo parseInfo = info.Copy();
		MangoMap map;

		while (ParseVariableAssignment(tokens, parseInfo, false) || ParseTemplateAssignment(tokens, parseInfo, false));

		while (true) {
			if (Optional<Mango> item = ParseVariable(tokens, parseInfo, true)) {
				if (item->type != MangoType::Map) {
					throw MangoDecodeError("Map expected for variable unpacking");
				}

				for (const Pair<String, Mango>& pair : item->map) {
					map.Add(pair);
				}
			}
			else if (Optional<Mango> item = ParseTemplate(tokens, parseInfo, true)) {
				if (item->type != MangoType::Map) {
					throw MangoDecodeError("Map expected for template unpacking");
				}

				for (const Pair<String, Mango>& pair : item->map) {
					map.Add(pair);
				}
			}
			else if (Optional<Pair<String, Mango>> item = ParseMapItem(tokens, parseInfo)) {
				if (map.Contains(item->key)) {
					throw MangoDecodeError("Duplicate map key");
				}

				map.Add(*item);
			}
			else {
				break;
			}
		}

		return map;
	}

	inline Optional<Mango> Mango::ParseMap(TokenList<TokenType>& tokens, ParsingInfo& info) {
		if (tokens.Current().type != TokenType::OpenCurl) return nullptr;
		tokens.Advance();

		MangoMap map = ParseMapItems(tokens, info);

		if (tokens.Current().type != TokenType::CloseCurl) {
			throw MangoDecodeError("'}' expected");	
		}

		tokens.Advance();
		return Mango(map);
	}

	inline Optional<String> Mango::ParseRawString(TokenList<TokenType>& tokens, ParsingInfo& info) {
		if (tokens.Current().type == TokenType::String) {
			tokens.Advance();
			return tokens.PeekPrevious().value;
		}

		return nullptr;
	}

	inline Optional<String> Mango::ParseName(TokenList<TokenType>& tokens, ParsingInfo& info) {
		if (tokens.Current().type == TokenType::Name) {
			tokens.Advance();
			return tokens.PeekPrevious().value;
		}
		else if (Optional<String> str = ParseRawString(tokens, info)) {
			return *str;
		}

		return nullptr;
	}

	inline Optional<String> Mango::ParseLabel(TokenList<TokenType>& tokens, ParsingInfo& info) {
		const UInt pos = tokens.GetPos();

		if (Optional<String> lbl = ParseName(tokens, info)) {
			if (tokens.Current().type == TokenType::Colon) {
				tokens.Advance();
				return lbl;
			}
		}

		tokens.SetPos(pos);
		return nullptr;
	}

	inline Optional<Mango> Mango::ParseValue(TokenList<TokenType>& tokens, ParsingInfo& info, const bool allowInnerLabels) {
		switch (tokens.Current().type) {
			case TokenType::Nil:      return ParseNil(tokens, info);
			case TokenType::Boolean:  return ParseBoolean(tokens, info);
			case TokenType::Number:   return ParseNumber(tokens, info);
			case TokenType::String:   return ParseString(tokens, info);
			case TokenType::OpenSq:   return ParseList(tokens, info);
			case TokenType::OpenCurl: return ParseMap(tokens, info);
			case TokenType::Var:      return ParseVariable(tokens, info);
			case TokenType::Template: return ParseTemplate(tokens, info);
			default: return nullptr;
		}
	}

	inline Optional<Mango> Mango::ParseLabeledValue(TokenList<TokenType>& tokens, ParsingInfo& info, const bool forceLabel) {
		const UInt pos = tokens.GetPos();
		Optional<String> label = ParseLabel(tokens, info);

		if (forceLabel && !label) {
			tokens.SetPos(pos);
			return nullptr;
		}

		if (Optional<Mango> mango = ParseValue(tokens, info)) {
			if (label) mango->SetLabel(*label);
			return *mango;
		}

		tokens.SetPos(pos);
		return nullptr;
	}

	inline bool Mango::ParseVariableAssignment(TokenList<TokenType>& tokens, ParsingInfo& info, const bool isList) {
		if (tokens.Current().type != TokenType::Var) return false;
		const UInt pos = tokens.GetPos();
		const String var = tokens.Current().value;
		tokens.Advance();

		if (tokens.Current().type == TokenType::Assign) {
			tokens.Advance();

			if (Optional<Mango> mango = ParseLabeledValue(tokens, info)) {
				if (info.variables.Contains(var)) {
					info.variables[var] = *mango;
				}
				else {
					info.variables.Add(var, *mango);
				}

				return true;
			}
			else {
				throw MangoDecodeError("Invalid variable assignment");
			}
 		}

		tokens.SetPos(pos);
		return false;
	}

	inline bool Mango::ParseTemplateAssignment(TokenList<TokenType>& tokens, ParsingInfo& info, const bool isList) {
		if (tokens.Current().type != TokenType::Template) return false;
		const UInt pos = tokens.GetPos();
		const String name = tokens.Current().value;
		tokens.Advance();

		if (tokens.Current().type != TokenType::OpenSq) {
			tokens.SetPos(pos);
			return false;
		}

		tokens.Advance();

		Template t;

		while (tokens.Current().type == TokenType::Var) {
			t.vars.Add(tokens.Current().value);
			tokens.Advance();
		}

		if (tokens.Current().type != TokenType::CloseSq) {
			tokens.SetPos(pos);
			return false;
		}

		tokens.Advance();

		if (tokens.Current().type != TokenType::Assign) {
			throw MangoDecodeError("'=' expected after template definition");
		}

		tokens.Advance();

		ParsingInfo parsingInfo = info.Copy();
		
		for (const String& var : t.vars) {
			Mango v = Mango(var);
			v.internalType = InternalType::Var;
			parsingInfo.variables.Set(var, v);
		}

		if (Optional<Mango> mango = ParseLabeledValue(tokens, parsingInfo)) {
			t.content = *mango;
			info.templates.Set(name, t);
			return true;
		}
		else {
			throw MangoDecodeError("Invalid template assignment");
		}
	}
}

#endif
