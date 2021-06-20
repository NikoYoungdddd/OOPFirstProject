#ifndef __STRUCTS_H__
#define __STRUCTS_H__

typedef struct sDamage
{
	
	unsigned int m_PhysicalDamage;  //物理伤害
	unsigned int m_PowerDamage;    //法术伤害
	sDamage()
	{
		m_PhysicalDamage = 0;
		m_PowerDamage = 0;
	}
	sDamage(const unsigned int phd, const unsigned int pod)
	{
		m_PhysicalDamage = phd;
		m_PowerDamage = pod;
	}

	sDamage& operator = (const sDamage& damage)
	{
		this->m_PhysicalDamage = damage.m_PhysicalDamage;
		this->m_PowerDamage = damage.m_PowerDamage;
		return *this;
	}


}DAMAGE;

typedef struct sDefense
{
	unsigned int m_PhysicalDefense;  //物抗
	unsigned int m_PowerDefense;   //法抗
	sDefense()
	{
		m_PhysicalDefense = 0;
		m_PowerDefense = 0;
	}
	sDefense(const unsigned int phd, const unsigned int pod)
	{
		m_PhysicalDefense = phd;
		m_PowerDefense = pod;
	}
	sDefense& operator = (const sDefense& defense)
	{
		this->m_PhysicalDefense = defense.m_PhysicalDefense;
		this->m_PowerDefense = defense.m_PowerDefense;
		return *this;
	}


}DEFENSE;

typedef struct sStatus
{
	DEFENSE m_Defense;  //攻击力
	DAMAGE m_Damage;   //防御力
	unsigned int m_AttackFrequency; //四秒内的攻击次数

	sStatus operator+(const sStatus& buff)
	{
		sStatus temp;
		temp.m_Damage.m_PhysicalDamage = this->m_Damage.m_PhysicalDamage + buff.m_Damage.m_PhysicalDamage;
		temp.m_Damage.m_PowerDamage = this->m_Damage.m_PowerDamage + buff.m_Damage.m_PowerDamage;
		temp.m_Defense.m_PhysicalDefense = this->m_Defense.m_PhysicalDefense + buff.m_Defense.m_PhysicalDefense;
		temp.m_Defense.m_PowerDefense = this->m_Defense.m_PowerDefense + buff.m_Defense.m_PowerDefense;
		temp.m_AttackFrequency = this->m_AttackFrequency + buff.m_AttackFrequency;
		return temp;
	}
	sStatus operator-(const sStatus& debuff)
	{
		sStatus temp;
		temp.m_Damage.m_PhysicalDamage = this->m_Damage.m_PhysicalDamage - debuff.m_Damage.m_PhysicalDamage;
		temp.m_Damage.m_PowerDamage = this->m_Damage.m_PowerDamage - debuff.m_Damage.m_PowerDamage;
		temp.m_Defense.m_PhysicalDefense = this->m_Defense.m_PhysicalDefense - debuff.m_Defense.m_PhysicalDefense;
		temp.m_Defense.m_PowerDefense = this->m_Defense.m_PowerDefense - debuff.m_Defense.m_PowerDefense;
		temp.m_AttackFrequency = this->m_AttackFrequency - debuff.m_AttackFrequency;
		return temp;
	}
	sStatus()
	{
		m_Damage.m_PhysicalDamage = 0;
		m_Damage.m_PowerDamage = 0;
		m_Defense.m_PhysicalDefense = 0;
		m_Defense.m_PowerDefense = 0;
		m_AttackFrequency = 0;
	}
	sStatus(const DEFENSE& defense, const DAMAGE& damage, const unsigned int frequence)
	{
		this->m_Defense = defense;
		this->m_Damage = damage;
		this->m_AttackFrequency = frequence;
	}

	sStatus(const unsigned int physicdefense, const unsigned int powerdefense,
		const unsigned int physicdamage, const unsigned int powerdamage,
		const unsigned int frequency)
	{
		this->m_Defense.m_PhysicalDefense = physicdefense;
		this->m_Defense.m_PowerDefense = powerdefense;
		this->m_Damage.m_PhysicalDamage = physicdamage;
		this->m_Damage.m_PowerDamage = powerdamage;
		this->m_AttackFrequency = frequency;
	}

	sStatus& operator*=(float ft)
	{

		this->m_Defense.m_PhysicalDefense =
			static_cast<unsigned int>(m_Defense.m_PhysicalDefense * ft);
		this->m_Defense.m_PhysicalDefense =
			static_cast<unsigned int> (m_Defense.m_PhysicalDefense * ft);
		this->m_Defense.m_PowerDefense =
			static_cast<unsigned int> (m_Defense.m_PowerDefense * ft);
		this->m_Damage.m_PhysicalDamage =
			static_cast<unsigned int> (m_Damage.m_PhysicalDamage * ft);
		this->m_Damage.m_PowerDamage =
			static_cast<unsigned int> (m_Damage.m_PowerDamage * ft);
		this->m_AttackFrequency =
			static_cast<unsigned int>(m_AttackFrequency * ft);

		return (*this);
	}

} STATUS;

#endif
