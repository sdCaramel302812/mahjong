#pragma once
class GM
{
public:
	GM();
	~GM();

	void NextKyouku();
	void NakuCheck();
	void NextPlayer();

	int CurrentPlayer = 1;
};

