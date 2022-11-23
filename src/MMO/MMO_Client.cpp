#include "../../libs/MMO/MMO_Common.h"

#define OLC_PGEX_TRANFORMEDVIEW
#include "../../libs/MMO/olcPGEX_TransformedView.h" 

class MMOGame : public olc::PixelGameEngine, olc::net::client_interface<GameMsg>
{
public:
	MMOGame()
	{
		sAppName = "MMO Client";
	}
private:
    olc::TileTransformedView tv;

    std::string sWorldMap =
		"################################"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..........####...####.........#"
		"#..........#.........#.........#"
		"#..........#.........#.........#"
		"#..........#.........#.........#"
		"#..........##############......#"
		"#..............................#"
		"#..................#.#.#.#.....#"
		"#..............................#"
		"#..................#.#.#.#.....#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"################################";

	olc::vi2d vWorldSize = { 32, 32 };

public:
	bool OnUserCreate() override
	{
        tv = olc::TileTransformedView({ ScreenWidth(), ScreenHeight() }, { 8, 8 });
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
        if (GetMouse(2).bPressed) tv.StartPan(GetMousePos());
		if (GetMouse(2).bHeld) tv.UpdatePan(GetMousePos());
		if (GetMouse(2).bReleased) tv.EndPan(GetMousePos());
		if (GetMouseWheel() > 0) tv.ZoomAtScreenPos(1.5f, GetMousePos());
		if (GetMouseWheel() < 0) tv.ZoomAtScreenPos(0.75f, GetMousePos());

		// Clear World
		Clear(olc::BLACK);

		// Draw World
		olc::vi2d vTL = tv.GetTopLeftTile().max({ 0,0 });
		olc::vi2d vBR = tv.GetBottomRightTile().min(vWorldSize);
		olc::vi2d vTile;
		for (vTile.y = vTL.y; vTile.y < vBR.y; vTile.y++)
			for (vTile.x = vTL.x; vTile.x < vBR.x; vTile.x++)
			{
				if (sWorldMap[vTile.y * vWorldSize.x + vTile.x] == '#')
				{
					tv.DrawRect(vTile, { 1.0f, 1.0f });
					tv.DrawRect(olc::vf2d(vTile) + olc::vf2d(0.1f, 0.1f), { 0.8f, 0.8f });
				}
			}
		return true;
	}
};

int main()
{
	MMOGame demo;
	if (demo.Construct(680, 480, 2, 2))
		demo.Start();
	return 0;
}