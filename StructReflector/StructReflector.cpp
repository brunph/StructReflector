#include "StructReflector.hpp"

namespace sreflect
{
	std::string StructReflector::reflect()
	{
		std::stringstream ss;

		ss << "struct " << m_structName << "\n{\n";

		for (auto& field : m_fields)
		{
			if (m_currentOffset < field->getOffset())
			{
				size_t dif = field->getOffset() - m_currentOffset;

				PadField pad(dif, m_currentOffset);
				ss << "	" << pad.getString() << " // 0x" << std::hex << m_currentOffset << "\n";
				
				m_currentOffset += pad.getSize();
			}

			ss << "	" << field->getString() << " // 0x" << std::hex << m_currentOffset << "\n";
			m_currentOffset += field->getSize();
		}

		ss << "};";

		return ss.str();
	}
}

