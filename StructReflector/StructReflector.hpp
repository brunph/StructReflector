#pragma once

#include <string>
#include <format>
#include <vector>
#include <sstream>

namespace sreflect
{
	class StructField
	{
	protected:
		size_t m_offset;
		std::string m_name;
	public:
		StructField(std::string name, size_t offset)
			: m_name(name), m_offset(offset)
		{ }

		virtual std::string getString() = 0;
		virtual size_t getSize() = 0;

		size_t getOffset()
		{
			return m_offset;
		}
	};

	class BoolField : public StructField
	{
	public:
		BoolField(std::string name, size_t offset) : StructField(std::move(name), offset)
		{ }

		std::string getString() override
		{
			return std::format("bool {};", m_name);
		}

		size_t getSize() override
		{
			return 1;
		}
	};
	
	class IntField : public StructField
	{
	public:
		IntField(std::string name, size_t offset) : StructField(std::move(name), offset)
		{ }

		std::string getString() override
		{
			return std::format("int32_t {};", m_name);
		}

		size_t getSize() override
		{
			return 4;
		}
	};

	class UIntField : public StructField
	{
	public:
		UIntField(std::string name, size_t offset) : StructField(std::move(name), offset)
		{ }

		std::string getString() override
		{
			return std::format("uint32_t {};", m_name);
		}

		size_t getSize() override
		{
			return 4;
		}
	};

	class Int64Field : public StructField
	{
	public:
		Int64Field(std::string name, size_t offset) : StructField(std::move(name), offset)
		{ }

		std::string getString() override
		{
			return std::format("int64_t {};", m_name);
		}

		size_t getSize() override
		{
			return 8;
		}
	};

	class UInt64Field : public StructField
	{
	public:
		UInt64Field(std::string name, size_t offset) : StructField(std::move(name), offset)
		{ }

		std::string getString() override
		{
			return std::format("uint64_t {};", m_name);
		}

		size_t getSize() override
		{
			return 8;
		}
	};

	class CharField : public StructField
	{
	private:
		size_t m_size;
	public:
		CharField(std::string name, size_t offset, size_t size) : StructField(std::move(name), offset), m_size(size)
		{ }

		std::string getString() override
		{
			return std::format("char {}[{}];", m_name, m_size);
		}

		size_t getSize() override
		{
			return m_size;
		}
	};

	class CharPtrField : public StructField
	{
	public:
		CharPtrField(std::string name, size_t offset) : StructField(std::move(name), offset)
		{ }

		std::string getString() override
		{
			return std::format("char* {};", m_name);
		}

		size_t getSize() override
		{
			return 8;
		}
	};

	class PadField : public StructField
	{
	private:
		size_t m_padSize;
	public:
		PadField(size_t padSize, size_t offset) :
			StructField(std::format("{:04x}", offset), offset), m_padSize(padSize)
		{ }

		std::string getString() override
		{
			return std::format("char pad_{}[{}];", m_name, m_padSize);
		}
	
		size_t getSize() override
		{
			return m_padSize;
		}
	};

	class StructReflector
	{
	private:
		std::vector<std::shared_ptr<StructField>> m_fields;
		std::string m_structName;

		size_t m_currentOffset{};
	public:
		StructReflector(std::string name)
			: m_structName(name)
		{ }

		template <typename T>
		StructReflector& addField(T&& field)
		{
			auto ptr = std::make_shared<std::remove_reference_t<T>>(field);

			this->m_fields.push_back(std::move(ptr));

			return *this;
		}


		std::string reflect();
	};
}

