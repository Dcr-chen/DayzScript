class ActionDeconstructShelter : ActionContinuousBase
{
	void ActionDeconstructShelter()
	{
		m_CallbackClass		= ActionPackTentCB;
		m_SpecialtyWeight 	= UASoftSkillsWeight.PRECISE_LOW;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_DEPLOY_2HD;
		m_FullBody			= true;
		m_StanceMask		= DayZPlayerConstants.STANCEMASK_CROUCH;
		m_Text 				= "#pack_tent";
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionTarget 	= new CCTCursor(UAMaxDistances.DEFAULT);
		m_ConditionItem 	= new CCINone();
	}
	
	override typename GetInputType()
	{
		return ContinuousInteractActionInput;
	}
	override bool HasProgress()
	{
		return true;
	}
	
	override bool HasAlternativeInterrupt()
	{
		return true;
	}
	
	override bool ActionConditionContinue(ActionData action_data)
	{
		return true;
	}
	
	override ActionData CreateActionData()
	{
		PlaceObjectActionData action_data = new PlaceObjectActionData();
		return action_data;
	}
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{	
		if (player.GetBrokenLegs() == eBrokenLegs.BROKEN_LEGS)
			return false;
		
		Object targetObject = target.GetObject();
		if (targetObject)
		{
			ShelterBase shelter = ShelterBase.Cast(targetObject);
			return shelter && shelter.CanBePacked();
		}

		return false;
	}
	
	override void OnStart(ActionData action_data)
	{
		super.OnStart(action_data);

		action_data.m_Player.TryHideItemInHands(true);
	}
	
	override void OnEnd(ActionData action_data)
	{
		super.OnEnd(action_data);

		action_data.m_Player.TryHideItemInHands(false);
	}
	
	override void OnFinishProgressServer(ActionData action_data)
	{
		ShelterBase shelter = ShelterBase.Cast(action_data.m_Target.GetObject());
		if (shelter)
			shelter.Deconstruct();
	}
	
	override string GetAdminLogMessage(ActionData action_data)
	{
		return " packed " + action_data.m_Target.GetObject().GetDisplayName() + " with Hands ";
	}
}
