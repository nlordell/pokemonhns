.set LOCALID_LASS, 2
.set LOCALID_SILVER, 3

NewBarkTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, NewBarkTown_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

NewBarkTown_OnFrame::
	map_script_2 VAR_NEWBARK_TOWN_STATE, 6, NewBarkTown_EventScript_ElmCallAfterLeague
	.2byte 0

NewBarkTown_EventScript_ElmCallAfterLeague::
	lock
	pokenavcall BlackthornCity_Text_ElmCall
	waitmessage
	delay 30
	setvar VAR_NEWBARK_TOWN_STATE, 7
	setvar VAR_NEWBARKTOWN_LABSTATE, 10
	release
	end

NewBarkTown_OnTransition::
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_Set_TalkToElm
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_Set_TalkToMom
	end

NewBarkTown_Set_TalkToElm::
	clearflag FLAG_HIDE_SILVER_NEWBARKTOWN
	setobjectxyperm LOCALID_LASS, 0, 11
	callnative SetTimeBasedEncounters
	end

NewBarkTown_Set_TalkToMom::
	setobjectxyperm LOCALID_LASS, 0, 11
	callnative SetTimeBasedEncounters
	end

NewBarkTown_EventScript_LabSign::
	msgbox NewBarkTown_Text_LabSign, MSGBOX_SIGN
	end

NewBarkTown_EventScript_TownSign::
	msgbox NewBarkTown_Text_Sign, MSGBOX_SIGN
	closemessage
	end


NewBarkTown_EventScript_Lass::
	lock
	faceplayer
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_LassState2
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 3, NewBarkTown_EventScript_LassState3
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_EventScript_LassState4
	msgbox NewBarkTown_Text_LassState5, MSGBOX_DEFAULT
	closemessage
	release
	end
	
NewBarkTown_EventScript_LassState2::
	playse SE_PIN
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
	waitmovement 0
	faceplayer
	waitmovement 0
	msgbox NewBarkTown_Text_LassState2, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_LassState3::
	msgbox NewBarkTown_Text_LassState3, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_LassState4::
	playse SE_PIN
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
	waitmovement 0
	faceplayer
	waitmovement 0
	msgbox NewBarkTown_Text_LassState4, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_Wooper::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WOOPER, CRY_MODE_NORMAL
	msgbox NewBarkTown_Text_Wooper, MSGBOX_DEFAULT
	waitmoncry
	release
	end

NewBarkTown_EventScript_LeaveTrigger::
	lock
	call_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_LeaveTriggersState2
	call_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_EventScript_LeaveTriggersState4
	applymovement OBJ_EVENT_ID_PLAYER, OldaleTown_Movement_PlayerStepBack
	waitmovement 0
	release
	end

NewBarkTown_EventScript_LeaveTriggersState2::
	playse SE_PIN
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_LASS, NewBarkTown_Movement_FaceDown
	waitmovement 0
	msgbox NewBarkTown_Text_LassState2, MSGBOX_DEFAULT
	closemessage
	return

NewBarkTown_EventScript_LeaveTriggersState4::
	playse SE_PIN
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_LASS, NewBarkTown_Movement_FaceDown
	waitmovement 0
	msgbox NewBarkTown_Text_LassState4, MSGBOX_DEFAULT
	closemessage
	return 



NewBarkTown_EventScript_FatMan::
	lock
	faceplayer
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_FatManState2
	msgbox NewBarkTown_Text_FatManState3, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_FatManState2::
	msgbox NewBarkTown_Text_FatManState2, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_Silver::
	lock
	msgbox NewBarkTown_Text_Silver1, MSGBOX_DEFAULT
	delay 60
	playse SE_PIN
	applymovement LOCALID_SILVER, Common_Movement_ExclamationMark
	faceplayer
	waitmovement 0
	msgbox NewBarkTown_Text_Silver2, MSGBOX_DEFAULT
	playse SE_BANG
	applymovement LOCALID_SILVER, NewBarkTown_Movement_SilverPushesPlayer
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerPushedBySilver
	waitmovement 0
	applymovement LOCALID_SILVER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	waitmovement 0
	release
	end


NewBarkTown_EventScript_Door::
	msgbox NewBarkTown_Text_Door, MSGBOX_SIGN
	end


NewBarkTown_EventScript_HelperMan1::
	lock
	faceplayer
	goto_if_unset FLAG_IS_CHAMPION, HelperMan_EventScript_NotChampion
	msgbox HelperMan_Text_GiftBPs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HelperMan_EventScript_Declined
	givebp 42
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	release
	end

NewBarkTown_EventScript_HelperMan2::
	lock
	faceplayer
	goto_if_unset FLAG_IS_CHAMPION, HelperMan_EventScript_NotChampion
	msgbox HelperMan_Text_ResetEVs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HelperMan_EventScript_Declined
	nlordell_resetevs
	msgbox HelperMan_Text_ResetEVsComplete, MSGBOX_DEFAULT
	release
	end

NewBarkTown_EventScript_HelperMan3::
	lock
	faceplayer
	goto_if_unset FLAG_IS_CHAMPION, HelperMan_EventScript_NotChampion
	msgbox HelperMan_Text_ReRandomize, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HelperMan_EventScript_Declined
	nlordell_rerandomize
	msgbox HelperMan_Text_ReRandomizeComplete, MSGBOX_DEFAULT
	release
	end

HelperMan_EventScript_NotChampion::
	msgbox HelperMan_Text_NotChampion, MSGBOX_DEFAULT
	release
	end

HelperMan_EventScript_Declined::
	msgbox HelperMan_Text_Declined, MSGBOX_DEFAULT
	release
	end


NewBarkTown_EventScript_TestMan1::
	givebp 4
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	end

NewBarkTown_EventScript_TestMan2::
	setvar VAR_NEWBARK_TOWN_STATE, 4
	setflag FLAG_HIDE_MOMS_FRIEND
	setflag FLAG_ADVENTURE_STARTED
	setflag FLAG_HIDE_SILVER_NEWBARKTOWN
	end

NewBarkTown_EventScript_TestMan3::
	setvar VAR_NEWBARK_TOWN_STATE, 5
	
	clearflag FLAG_COMPLETED_AERODACTYL_PUZZLE
	clearflag FLAG_COMPLETED_HOOH_PUZZLE
	clearflag FLAG_COMPLETED_KABUTO_PUZZLE
	clearflag FLAG_COMPLETED_OMANYTE_PUZZLE
	end

NewBarkTown_Movement_SilverPushesPlayer:
	walk_fast_left
	walk_fast_left
	walk_fast_down
	face_down
	lock_facing_direction
	unlock_facing_direction
	walk_fast_up
	walk_fast_right
	walk_fast_right
	step_end


NewBarkTown_Movement_PlayerPushedBySilver:
	walk_fast_left
	face_up
	walk_fast_down
	face_up
	lock_facing_direction
	jump_2_down
	unlock_facing_direction
	face_down
	step_end

	


NewBarkTown_Movement_FaceDown:
	face_down
	step_end

NewBarkTown_Text_LabSign:
	.string "PROF.ELM'S LAB$"

NewBarkTown_Text_Door:
	.string "The door is locked.$"

NewBarkTown_Text_Wooper:
	.string "WOOPER: Woooooop.$"

NewBarkTown_Text_FatManState2:
	.string "Wow, your POKéGEAR is impressive!\n"
	.string "Did your mom get it for you?$"

NewBarkTown_Text_FatManState3:
	.string "Yo, {PLAYER}!\p"
	.string "I hear PROF.ELM discovered\n"
	.string "some new POKéMON.$"

NewBarkTown_Text_LassState2:
	.string "Wait, {PLAYER}!\p"
	.string "It's dangerous to go out\n"
	.string "without a POKéMON!\p"
	.string "Wild POKéMON jump out of the grass\n"
	.string "on the way to the next town.$"

NewBarkTown_Text_LassState3:
	.string "Oh! Your POKéMON is adorable!\n"
	.string "I wish I had one!$"

NewBarkTown_Text_LassState4:
	.string "Hi, {PLAYER}! Leaving again?\p"
	.string "You should tell your mom if\n"
	.string "you are leaving.$"

NewBarkTown_Text_LassState5:
	.string "Call your mom on your POKéGEAR\n"
	.string "to let her know how you're doing.$\p"

NewBarkTown_Text_Silver1:
	.string ". . .\p"
	.string "So this is the famous ELM\n"
	.string "POKéMON LAB…$"

NewBarkTown_Text_Silver2:
	.string "…What are you staring at?$"

NewBarkTown_Text_Sign:
	.string "NEW BARK TOWN\p"
	.string "The Town Where the Winds of\n"
	.string "a New Beginning Blow$"

NewBarkTown_EventScript_PlayersHouseMailbox::
	msgbox NewBarkTown_Text_PlayersHouse, MSGBOX_SIGN
	end

NewBarkTown_EventScript_ElmsHouseMailbox::
	msgbox NewBarkTown_Text_ElmsHouse, MSGBOX_SIGN
	end

NewBarkTown_Text_PlayersHouse:
	.string "{PLAYER}'S HOUSE$"

NewBarkTown_Text_ElmsHouse:
	.string "PROF.ELM'S HOUSE$"


HelperMan_Text_NotChampion:
	.string "Come back when you're champion.$"

HelperMan_Text_GiftBPs:
	.string "I can give you a few BATTLE\n"
	.string "POINTS because you look nice.$"

HelperMan_Text_ResetEVs:
	.string "I can reset the EVs for your\n"
	.string "active POKéMON back to 0.$"

HelperMan_Text_ReRandomize:
	.string "I can re-randomize your active\n"
	.string "POKéMON.$"

HelperMan_Text_ResetEVsComplete:
	.string "All done, your POKéMON EVs\n"
	.string "have been reset to 0!$"

HelperMan_Text_ReRandomizeComplete:
	.string "Your POKéMON's IVs are now:\n"
	.string "{STR_VAR_1}.$"

HelperMan_Text_Declined:
	.string "Come back whenever!$"
