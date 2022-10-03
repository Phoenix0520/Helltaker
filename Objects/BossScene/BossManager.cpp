#include "framework.h"
#include "BossManager.h"
#include "HS17_BossScene.h"
#include "ChainVH.h"
#include "Helltaker.h"

BossManager::BossManager()
{
	for (UINT i = 0; i < 12; i++)
	{
		ChainVH* chain = (ChainVH*)OBJMANAGER->FindObject("ChainVH" + to_string(i));
		chain->SetPosByID(i);
		chain->Reset();
		chains.push_back(chain);
	}

	activated.resize(200);
}

BossManager::~BossManager()
{
	for (UINT i = 0; i < 12; i++)
		SAFE_DELETE(chains[i])
}

void BossManager::Update(Matrix V, Matrix P)
{
	if (push == end)
		return;

	if (times[push] <= 0.0f)
	{
		if (!reset)
		{
			for (UINT j = 0; j < activated[push].size(); j++)
			{
				cout << activated[push][j] << " ";
				chains[activated[push][j]]->Reset();
			}
			cout << "번째 체인 호출" << endl;
			reset = true;
		}
		if (end > push)
		{
			push++;
			attack = false;
			reset = false;
			return;
		}
	}
	else
	{
		times[push] -= DELTA;
	}

	for (UINT i = 0; i < activated[push].size(); i++)
	{
		int index = activated[push][i];
		chains[index]->Update(V, P);

		Helltaker* ht = (Helltaker*)OBJMANAGER->FindObject("Helltaker");

		if (chains[index]->IsAttacking())
		{
			if (Collider::InterSect(chains[index]->GetCollider(), ht->GetCollider()))
			{
				if (!attack)
				{
					HS17_BossScene* scene = (HS17_BossScene*)SCENEMANAGER->GetScene("HS17_BossScene");

					//if (!ht->GetImmune())
						//scene->DiscardLife();
					attack = true;
				}
			}
		}
	}
}

void BossManager::Render()
{
	if (push == end)
		return;

	for (UINT i = 0; i < activated[push].size(); i++)
	{
		chains[activated[push][i]]->Render();
	}
}

void BossManager::Reset()
{
	push = 0;
	end = 0;
	attack = false;
	activated.clear();
	activated.resize(200);
	times.clear();
}

void BossManager::PushChain(int type, int value, float time)
{
	if (type == 0)
	{
		for (UINT i = 0; i < 7; i++)
		{
			int comp = pow(2, i) * pow(8, i);

			if ((value & comp) == comp)
			{
				cout << i << " ";
				activated[end].push_back(i);
			}
		}
	}
	else
	{
		for (UINT i = 0; i < 5; i++)
		{
			int comp = pow(2, i) * pow(8, i);

			if ((value & comp) == comp)
			{
				cout << i + 7 << " ";
				activated[end].push_back(i + 7);
			}
		}
	}


	if (time != 0.0f)
	{
		end++;
		times.push_back(time);
		cout << endl;
	}
}
