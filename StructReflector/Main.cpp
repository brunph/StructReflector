#include "StructReflector.hpp"

int main()
{
	using namespace sreflect;

	StructReflector strct("TestStruct");

	strct.addField(BoolField("m_boolField1", 0x18));
	strct.addField(BoolField("m_boolField2", 0x19));
	strct.addField(BoolField("m_boolField3", 27));
	strct.addField(CharField("m_charField", 0x50, 20));
	strct.addField(IntField("m_intField", 0x80));

	printf("%s\n", strct.reflect().data());
}