class NurseDress_ColorBase extends Top_Base
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionWringClothes);
	}
};
class NurseDress_White extends NurseDress_ColorBase {};
class NurseDress_Blue extends NurseDress_ColorBase {};