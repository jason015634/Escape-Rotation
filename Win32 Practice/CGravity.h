#pragma once



class CGravity
{
private:
	CObject* m_pOwner;

	bool m_bGround;

public:
	void SetGround(bool _b);
public:
	void finalupdate();
	bool isGround() { return m_bGround; }
public:
	CGravity();
	~CGravity();

	friend class CObject;
};

