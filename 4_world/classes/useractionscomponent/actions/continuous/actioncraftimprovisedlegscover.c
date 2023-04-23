class ActionCraftImprovisedLegsCoverCB : ActionContinuousBaseCB
{
	private const float TIME_TO_CRAFT_CLOTHES = 5.0;
	
	override void CreateActionComponent()
	{
		//float adjusted_time = m_ActionData.m_Player.GetSoftSkillsManager().AdjustCraftingTime(TIME_TO_CRAFT_CLOTHES,UASoftSkillsWeight.ROUGH_HIGH);	
		m_ActionData.m_ActionComponent = new CAContinuousTime(TIME_TO_CRAFT_CLOTHES);
	}
};

class ActionCraftImprovisedLegsCover: ActionContinuousBase
{
	void ActionCraftImprovisedLegsCover()
	{
		m_CallbackClass = ActionCraftImprovisedLegsCoverCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_CRAFTING;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
		m_Text = "#STR_CraftImprovisedLegsCover";
	}
	
	override void CreateConditionComponents()  
	{		
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if( item.GetQuantity() == 6 )
		{
			return true;
		}
		return false;
	}
	
	override bool HasTarget()
	{
		return false;
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		EntityAI item_ingredient = action_data.m_MainItem;
		EntityAI cover;
		
		cover = action_data.m_Player.SpawnEntityOnGroundPos("LegsCover_Improvised", action_data.m_Player.GetPosition());
		action_data.m_MainItem.AddQuantity(-6);
		
		MiscGameplayFunctions.TransferItemProperties(item_ingredient, cover);
	}
};
