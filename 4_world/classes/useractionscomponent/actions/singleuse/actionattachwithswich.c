class ActionAttachWithSwitch: ActionAttach
{
	void ActionAttachWithSwitch()
	{
	}

	override void CreateConditionComponents() 
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNonRuined( UAMaxDistances.DEFAULT );
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_ATTACHITEM;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
	}
	
	override typename GetInputType()
	{
		return InventoryOnlyActionInput;
	}
	
	override bool CanBePerformedFromInventory()
	{
		return true;
	}
	
	override ActionData CreateActionData()
	{
		AttachActionData action_data = new AttachActionData;
		return action_data;
	}
	
	override bool SetupAction(PlayerBase player, ActionTarget target, ItemBase item, out ActionData action_data, Param extra_data = NULL)
	{
		ref InventoryLocation il = new InventoryLocation;
		if (!GetGame().IsDedicatedServer())
		{
			EntityAI target_entity;
			
			if ( target.IsProxy() )
			{
				target_entity = EntityAI.Cast( target.GetParent() );
			}
			else
			{
				target_entity = EntityAI.Cast( target.GetObject() );
			}
			
			if (!target_entity.GetInventory().FindFreeLocationFor( item, FindInventoryLocationType.ATTACHMENT, il ))
				return false;
		}
			
		if ( super.SetupAction( player, target, item, action_data, extra_data))
		{
			if (!GetGame().IsDedicatedServer())
			{
				AttachActionData action_data_a = AttachActionData.Cast(action_data);
				action_data_a.m_AttSlot = il.GetSlot();
			}
			return true;
		}
		return false;
	}
	
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		EntityAI target_entity = EntityAI.Cast( target.GetObject() );
		if( !item.CanSwitchDuringAttach(target_entity) )
			return false;
		
		if ( target_entity && item )
		{
			if ( target_entity.GetInventory() && target_entity.GetInventory().CanAddAttachment( item ) )
			{
				return true;
			}
		}	
		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		if (GetGame().IsMultiplayer())
			return;
		
		ClearInventoryReservationEx(action_data);
		AttachActionData action_data_a = AttachActionData.Cast(action_data);
		EntityAI target_EAI;
			
		if ( action_data.m_Target.IsProxy() )
		{
			target_EAI = EntityAI.Cast( action_data_a.m_Target.GetParent() );
		}
		else
		{
			target_EAI = EntityAI.Cast( action_data_a.m_Target.GetObject() );
		}
		
		if (target_EAI && action_data_a.m_MainItem)
		{
			ref InventoryLocation il = new InventoryLocation;
			il.SetAttachment( target_EAI, action_data.m_MainItem, action_data_a.m_AttSlot );
			action_data.m_Player.PredictiveForceSwapEntities( target_EAI, action_data.m_MainItem, il );
		}
	}
	
	override void OnExecuteClient( ActionData action_data )
	{
		ClearInventoryReservationEx(action_data);
		AttachActionData action_data_a = AttachActionData.Cast(action_data);
		
		EntityAI target_EAI;
			
		if ( action_data.m_Target.IsProxy() )
		{
			target_EAI = EntityAI.Cast( action_data_a.m_Target.GetParent() );
		}
		else
		{
			target_EAI = EntityAI.Cast( action_data_a.m_Target.GetObject() );
		}
		
		if (target_EAI && action_data_a.m_MainItem)
		{
			ref InventoryLocation il = new InventoryLocation;
			il.SetAttachment( target_EAI, action_data.m_MainItem, action_data_a.m_AttSlot );
			action_data.m_Player.PredictiveForceSwapEntities( target_EAI, action_data.m_MainItem, il );
		}
	}
}