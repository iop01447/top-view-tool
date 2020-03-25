#pragma once

#define MAX_STR 256
#define MID_STR 128
#define MIN_STR 64

#define WINCX 800
#define WINCY 600
#define TILECX 32
#define TILECY 32
#define TILEX 30
#define TILEY 30

#define OFFSET 300

#define SWORD	0x01
#define AXE		0x02
#define BOW		0x04

#define NOCOPY(ClassName)						\
private:										\
	ClassName(ClassName& rObj) {};				\
	void operator=(ClassName& rObj) {}

#define DECLARE_SINGLETON(ClassName)			\
public:											\
static ClassName* Get_Instance()				\
{												\
	if (nullptr == m_pInstance)					\
		m_pInstance = new ClassName;			\
	return m_pInstance;							\
}												\
static void Destroy_Instance()					\
{												\
	if (m_pInstance)							\
	{											\
		delete m_pInstance;						\
		m_pInstance = nullptr;					\
	}											\
}												\
NOCOPY(ClassName)								\
private:										\
	static ClassName* m_pInstance;				


#define IMPLEMENT_SINGLETON(ClassName)			\
ClassName* ClassName::m_pInstance = nullptr;

#define GET_INSTANCE(ClassName)					\
ClassName::Get_Instance()