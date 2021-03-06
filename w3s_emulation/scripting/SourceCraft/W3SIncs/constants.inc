/**
* File: 
* 
*/





////#if !defined(MAXPLAYERS) //only for creating arrays, do not use this number as loop limit , use <=MaxClients variable
////#define MAXPLAYERS 66   //+1 of real for normal servers, add +X number of HLTV slots
////#endif


#define MAXRACES 100 //20 = [1]-[19]  ///can only hold X-1 races, IE 20 can only hold 19 races, we skip zeroth race!

#define MAXITEMS 40  // [1]-[19] //(+1 of real number of items, if there are 8 items to load, use 9!! ignore zeroth rule)
//zeroth item not used
/////#define MAXITEMPROPERTIES 1

#define MAXSKILLCOUNT 7 //0-6   //A SKILL IS GENERIC, set the property "ultimate" to true for ultmates

#define DEF_MAX_SKILL_LEVEL 4 //DO NOT CHANGE

#define MAXLEVELXPDEFINED 16 //maximum where level XP is defined, if a race has more than MAXLEVELXPDEFINED levles, xp given and xp to next level is still MAXLEVELXPDEFINED



enum W3Var
{
	OldRace, //the race he was before OnRaceSelected
	DeathRace, //race when player died 
	hDatabase,
	hDatabaseType,
	hSaveEnabledCvar,
	hRaceLimitEnabledCvar,
	hNewPlayerLevelbankCvar,
	REMOVEsafsdfes,
	TheItemBoughtOrLost,
	hPlayerInfoArgStr,
	RaceinfoRaceToShow,
	EventArg1,
	EventArg2,
	EventArg3,
	
	TransClient,//who to translate
	
	hUseMetricCvar,
	
	SmEvent, ///usual game events from sm hookked events
	
}

enum W3EVENT
{
	Moled,
	BombPlanted,
	BombDefused,
	ToBeRevived,
	DoShowHelpMenu,
	DoShowChangeRaceMenu,
	DoShowShopMenu,
	DoTriedToBuyItem,
	DoShowItemsInfoMenu,
	DoShowRaceinfoMenu,
	DoShowPlayerinfoMenu, 
	DoShowPlayerinfoEntryWithArg,
	DoShowParticularRaceInfo,

	ClearPlayerVariables,
	DoLevelCheck,
	
	OnPreGiveXPGold, //client, arg1,2,3=W3XPAwardedBy , xp, gold
	//sh
	
	
	
	//w3
	
	
	DoForwardClientBoughtItem, //tell item ownership to call lost and bought forwards
	DoForwardClientLostItem, //uses TheItemBoughtOrLost
	
	DoShowSpendskillsMenu,
	PlayerIsNewToServer,
	DoResetSkills,
	DoShowWar3Menu,
	DoShowLevelBank,
	DoShowWar3Rank,
	DoShowWar3Stats,
	DoShowWar3Top,
	
	PlayerLeveledUp,
	DoCheckRestrictedItems,
	OnPostGiveXPGold, ///xp gold already given, same args as pre
	
	CanBuyItem, //client, arg1=itemid, if eventarg2 is non zero, he can buy// you have to do the message on the reason why he can't buy
	
	OnDeathPre, //EventArg1 = attacker.  before w3 actual death forward is called to do some reading ( ie before items are lost)
	DoShowMenuMyInfo, //MOVE or remove?
	DoShowPlayerInfoTarget, ///EventArg1 = target = the person whos info is shown, client=SHOW TO 
}
enum W3XPAwardedBy{
	XPAwardByGeneric, ///not defined
	XPAwardByKill,
	XPAwardByAssist,
	XPAwardByWin,
	XPAwardByBomb, //defuse / explode
	XPAwardByHostage,
	XPAwardByPointCap,
	XPAwardByPointCapBlock,
	XPAwardByFlagCap,
}
//#define IMMUNITY_COUNT 5
// The types of immunities you can get/set from.
#if defined SOURCECRAFT
	#define War3Immunity Immunity
	#define Immunity_Items Immunity_ShopItems
	#define Immunity_Skills Immunity_Upgrades
	#define Immunity_HealthTake Immunity_HealthTaking
	#define Immunity_PhysicalDamage Immunity_HealthTaking
	#define Immunity_MagicDamage Immunity_Magic


	#define War3DamageOrigin DamageFrom
	#define W3DMGORIGIN_UNDEFINED DamageFrom_None
	#define W3DMGORIGIN_SKILL DamageFrom_Skills
	#define W3DMGORIGIN_ULTIMATE DamageFrom_Ultimates
	#define W3DMGORIGIN_ITEM DamageFrom_ShopItems

	#define War3DamageType DamageFrom
	#define W3DMGTYPE_TRUEDMG DamageFrom_None
	#define W3DMGTYPE_PHYSICAL DamageFrom_HealthTaking
	#define W3DMGTYPE_MAGIC DamageFrom_Magic
#else
enum War3Immunity
{
	Immunity_None = 0, //generic zero
	Immunity_Ultimates, // Immune from ultimates
	Immunity_PhysicalDamage, // Immune from health taking
	Immunity_MagicDamage, // Immune from magic based stuff (doesnt not include ultimates)
	Immunity_Items, // Immune from shop items
	Immunity_Skills, // Immune from all skills
};

enum War3DamageOrigin
{ //where damage is from   skill or ultimate etc
	W3DMGORIGIN_UNDEFINED=0,
	W3DMGORIGIN_SKILL,
	W3DMGORIGIN_ULTIMATE,
	W3DMGORIGIN_ITEM,
}
enum War3DamageType
{//damage types
	W3DMGTYPE_TRUEDMG=0,       //normal damage without accout for physical or magic armor
	W3DMGTYPE_PHYSICAL,
	W3DMGTYPE_MAGIC,
}
#endif

// Games that War3Source Supports
#if defined SOURCECRAFT
	#define Game_CS  cstrike
	#define Game_TF  tf2
	#define Game_DOD dod

	#define CS  cstrike
	#define TF  tf2
	#define DOD dod
#else
enum Game {
	Game_None=0,
	Game_CS=1,
	Game_DOD=2,
	Game_TF=3,
	
	CS=1,
	DOD=2,
	TF=3,
}
#endif

enum W3PlayerProp{
	CurrentRace,
	PendingRace,
	PlayerGold,
	iMaxHP,
	bIsDucking,
	
	bool:xpLoaded,
	Float:RaceChosenTime,
	bool:RaceSetByAdmin,
	bool:SpawnedOnce,
	Float:sqlStartLoadXPTime,
}

//EXCLUSIVE: buffs that do not stack with itself: gravity, invisblity, however to make them stack use a second property ie gravity2, invisibilty2
//////////////////Generally races use "buffvar" and items that wish to stack uses "varbuff2" and the final value is calculated: best of "buffvar" stacked with best of "buffvar2"
//STACKING: buffs that stack with itself
//EACH BUFF SHOULD HAVE A CONCENSUS ON WHAT TYPE OF VALUE IT USES: bool, int, float
///NOT ALL BUFFS HAVE THE SAME DENIES, some only need skill deny or item deny only
//#define MAX_BUFFS 50 //number of indexes, for creating the array


enum W3BuffProperties{
	any:DefaultValue=0, //array index 1
	BuffStackCacheType:BuffStackType=1, //array index 1
}
enum BuffStackCacheType{ //each buff can only have one stacking operation:aa
	DoNotCache=0,
	bHasOneTrue,
	iAbsolute, 
	fAbsolute,
	fStacked, /// all float multiplied
	
	fMaximum,
	fMinimum,
	iMinimum,
	ERRUNDEFINED=-99,
}


enum W3Buff {
	buffdummy=0,
	bBuffDenyAll, //DENY=not allowed to have any buffs, aka "purge"
	
	fLowGravitySkill, //0.4 ish?
	fLowGravityItem, //0.4 ish?
	bLowGravityDenyAll,
	
	fInvisibilitySkill, //0.4 ish?
	fInvisibilityItem, //0.4 ish?
	bInvisibilityDenyAll,
	bInvisibilityDenySkill,
	bDoNotInvisWeapon,
	bInvisWeaponOverride, //set true to use override amount, ONLY 1 RACE SHALL USE THIS AT A TIME PER CLIENT
	iInvisWeaponOverrideAmount, ///amolunt of 0-255 , do not have to set back to 255, just set bInvisWeaponOverride to false
	
	fMaxSpeed, //for increasing speeds only! MUST BE MORE THAN 1.0
	fSlow, //for decreeasing speeds only! MUST BE LESS THAN 1.0
	fSlow2, //for decreeasing speeds only! MUST BE LESS THAN 1.0. allows a race to have stacking slows
	
	
	bImmunitySkills, //is immune to skills
	bImmunityUltimates, // is immune to ultimates
	
	fAttackSpeed, //attack speed multipler!
	
	bStunned, //cannot shoot, cannot cast, cannot move
	bBashed, //cannot move
	bDisarm,//cannot shoot
	bSilenced,  //cannot cast 
	bHexed,  // no skill proc
	bPerplexed, //cannot use items / proc items
	
	bNoMoveMode,//move type none! overrrides all other movestypes
	bFlyMode,   //fly mode
	bFlyModeDeny,
	bNoClipMode,
	
	fArmorPhysical,
	fArmorMagic,
	
	//DO NOT USE GLOW FOR INVIS
	iGlowRed, //glowing the player 0-255
	iGlowGreen,
	iGlowBlue,
	iGlowAlpha, //careful this is like invisiblity
	iGlowPriority, //highest priority takes effect
	fGlowSetTime, //time is recorded, those with same prioirty will compete via time. not something u set
	
	//move
	bSlowImmunity,
	
	////////////////
	
	
	MaxBuffLoopLimitTemp, //this is a variable that is for loops, this number is automatically generated fromt the enum. 
}
stock MaxBuffLoopLimit=_:MaxBuffLoopLimitTemp;


//create an buffpropertiesarray[W3Buff][W3BuffProperties]; (separate from the array that stores every client's buffs)
//we fill the array with its properties
stock InitiateBuffPropertiesArray(buffpropertiesarray[W3Buff][W3BuffProperties]){
	
	for(new i=0;i<MaxBuffLoopLimit;i++){
		buffpropertiesarray[W3Buff:i][DefaultValue]=-99;
		buffpropertiesarray[W3Buff:i][BuffStackType]=ERRUNDEFINED;
	}
	
	buffpropertiesarray[buffdummy][DefaultValue]=false;
	buffpropertiesarray[buffdummy][BuffStackType]=bHasOneTrue;
	
	buffpropertiesarray[bBuffDenyAll][DefaultValue]=false;
	buffpropertiesarray[bBuffDenyAll][BuffStackType]=bHasOneTrue;
	
	buffpropertiesarray[fLowGravitySkill][DefaultValue]=1.0;
	buffpropertiesarray[fLowGravitySkill][BuffStackType]=fMinimum;
	
	buffpropertiesarray[fLowGravityItem][DefaultValue]=1.0;
	buffpropertiesarray[fLowGravityItem][BuffStackType]=fMinimum;
	
	buffpropertiesarray[ bLowGravityDenyAll ][DefaultValue]=false;
	buffpropertiesarray[ bLowGravityDenyAll ][BuffStackType]=bHasOneTrue;
	
	buffpropertiesarray[ fInvisibilitySkill ][DefaultValue]=1.0;
	buffpropertiesarray[ fInvisibilitySkill ][BuffStackType]=fMinimum;
	
	buffpropertiesarray[ fInvisibilityItem ][DefaultValue]=1.0;
	buffpropertiesarray[ fInvisibilityItem ][BuffStackType]=fMinimum;
	
	buffpropertiesarray[ bInvisibilityDenyAll ][DefaultValue]=false;
	buffpropertiesarray[ bInvisibilityDenyAll ][BuffStackType]=bHasOneTrue;
	
	buffpropertiesarray[ bInvisibilityDenySkill ][DefaultValue]=false;
	buffpropertiesarray[ bInvisibilityDenySkill ][BuffStackType]=bHasOneTrue;
		
	buffpropertiesarray[ bDoNotInvisWeapon ][DefaultValue]=false;
	buffpropertiesarray[ bDoNotInvisWeapon ][BuffStackType]=bHasOneTrue;	
	
	buffpropertiesarray[ bInvisWeaponOverride ][DefaultValue]=false;
	buffpropertiesarray[ bInvisWeaponOverride ][BuffStackType]=bHasOneTrue;	
	
	buffpropertiesarray[ iInvisWeaponOverrideAmount ][DefaultValue]=255;
	buffpropertiesarray[ iInvisWeaponOverrideAmount ][BuffStackType]=iMinimum;	
	
	buffpropertiesarray[ fMaxSpeed ][DefaultValue]=1.0;
	buffpropertiesarray[ fMaxSpeed ][BuffStackType]=fMaximum;
	
	buffpropertiesarray[ fSlow ][DefaultValue]=1.0;
	buffpropertiesarray[ fSlow ][BuffStackType]=fStacked;	
	
	buffpropertiesarray[ fSlow2 ][DefaultValue]=1.0;
	buffpropertiesarray[ fSlow2 ][BuffStackType]=fStacked;
	

//	buffpropertiesarray[ fIncomingDamage ][DefaultValue]=1.0;
//	buffpropertiesarray[ fIncomingDamage ][BuffStackType]=fStacked;
	
	buffpropertiesarray[ bImmunitySkills ][DefaultValue]=false;
	buffpropertiesarray[ bImmunitySkills ][BuffStackType]=bHasOneTrue;	
	
	buffpropertiesarray[ bImmunityUltimates ][DefaultValue]=false;
	buffpropertiesarray[ bImmunityUltimates ][BuffStackType]=bHasOneTrue;	
	
	buffpropertiesarray[ fAttackSpeed ][DefaultValue]=1.0;
	buffpropertiesarray[ fAttackSpeed ][BuffStackType]=fStacked;
	
	buffpropertiesarray[ bStunned ][DefaultValue]=false;
	buffpropertiesarray[ bStunned ][BuffStackType]=bHasOneTrue;	
	
	buffpropertiesarray[ bBashed ][DefaultValue]=false;
	buffpropertiesarray[ bBashed ][BuffStackType]=bHasOneTrue;	
	
	buffpropertiesarray[ bDisarm ][DefaultValue]=false;
	buffpropertiesarray[ bDisarm ][BuffStackType]=bHasOneTrue;	
	
	buffpropertiesarray[ bSilenced ][DefaultValue]=false;
	buffpropertiesarray[ bSilenced ][BuffStackType]=bHasOneTrue;	
	
	buffpropertiesarray[ bPerplexed ][DefaultValue]=false;
	buffpropertiesarray[ bPerplexed ][BuffStackType]=bHasOneTrue;	
		
	buffpropertiesarray[ bHexed ][DefaultValue]=false;
	buffpropertiesarray[ bHexed ][BuffStackType]=bHasOneTrue;
		
	buffpropertiesarray[ bNoMoveMode ][DefaultValue]=false;
	buffpropertiesarray[ bNoMoveMode ][BuffStackType]=bHasOneTrue;	
	
	buffpropertiesarray[ bFlyMode ][DefaultValue]=false;
	buffpropertiesarray[ bFlyMode ][BuffStackType]=bHasOneTrue;	
	
	buffpropertiesarray[ bFlyModeDeny ][DefaultValue]=false;
	buffpropertiesarray[ bFlyModeDeny ][BuffStackType]=bHasOneTrue;	
	
	
	buffpropertiesarray[ bNoClipMode ][DefaultValue]=false;
	buffpropertiesarray[ bNoClipMode ][BuffStackType]=bHasOneTrue;	
	
	
	buffpropertiesarray[ fArmorPhysical ][DefaultValue]=0;
	buffpropertiesarray[ fArmorPhysical ][BuffStackType]=fAbsolute;	
	
	buffpropertiesarray[ fArmorMagic ][DefaultValue]=0;
	buffpropertiesarray[ fArmorMagic ][BuffStackType]=fAbsolute;	
	
	buffpropertiesarray[ iGlowRed ][DefaultValue]=255;
	buffpropertiesarray[ iGlowRed ][BuffStackType]=DoNotCache;
	
	buffpropertiesarray[ iGlowGreen ][DefaultValue]=255;
	buffpropertiesarray[ iGlowGreen ][BuffStackType]=DoNotCache;
	
	buffpropertiesarray[ iGlowBlue ][DefaultValue]=255;
	buffpropertiesarray[ iGlowBlue ][BuffStackType]=DoNotCache;
	
	buffpropertiesarray[ iGlowAlpha ][DefaultValue]=255;
	buffpropertiesarray[ iGlowAlpha ][BuffStackType]=DoNotCache;	
	
	buffpropertiesarray[ iGlowPriority ][DefaultValue]=0;
	buffpropertiesarray[ iGlowPriority ][BuffStackType]=DoNotCache;	
	
	buffpropertiesarray[ fGlowSetTime ][DefaultValue]=0;
	buffpropertiesarray[ fGlowSetTime ][BuffStackType]=DoNotCache;	
	
	//move	
	buffpropertiesarray[ bSlowImmunity ][DefaultValue]=false;
	buffpropertiesarray[ bSlowImmunity ][BuffStackType]=bHasOneTrue;
	
	
	//check that all indexes have been set
	for(new i=0;i<MaxBuffLoopLimit;i++){
		if(buffpropertiesarray[W3Buff:i][DefaultValue]==-99){
			SetFailState("Buff index %d [DefaultValue] was not set properly!",i);
		}
		if(buffpropertiesarray[W3Buff:i][BuffStackType]==ERRUNDEFINED){
			SetFailState("Buff index %d [BuffStackType] was not set properly!",i);
		}
	}
	
}

///not yet used
enum RaceString{
	RaceName,
	RaceShortname,
	RaceStory,
	RaceDescription,
	RaceTechnical,
}
enum SkillString{
	SkillName,
	SkillStory,
	SkillDescription,
	SkillTechnical,
}


enum  { //W3GlowPriority
	GLOW_NONE=0,
	GLOW_BASE=1, //if ur race needs a glow
	GLOW_BASE2, //temporary glow of ur race over ur orignal glow? like mole u can add a glow for another priority
	GLOW_DEFAULT,
	GLOW_SKILL, //if skill activates on u  or others
	GLOW_ULTIMATE, //if ultimate actiavates on u or others
	GLOW_OVERRIDE=255, //override all glow
}

enum W3ItemProp {
	ITEM_USED_ON_BUY=0,
	ITEM_SELFSTACK,
}



enum War3SQLType
{
	SQLType_Unknown = 0,
	SQLType_MySQL,
	SQLType_SQLite,
}




// The following are color presets for the War3_FlashScreen function
#if !defined RGBA_COLOR_RED
#define RGBA_COLOR_RED		{255,0,0,4}
#define RGBA_COLOR_GREEN	{0,255,0,3}
#define RGBA_COLOR_BLUE		{0,0,255,3}
#define RGBA_COLOR_YELLOW	{255,255,0,3}
#define RGBA_COLOR_ORANGE	{255,69,0,3}
#define RGBA_COLOR_PURPLE	{128,0,128,3}
#define RGBA_COLOR_CYAN		{255,0,255,3}
#define RGBA_COLOR_WHITE	{255,255,255,3}
#define RGBA_COLOR_BLACK	{0,0,0,3}
#define RGBA_COLOR_GREY		{128,128,128,3}
#define RGBA_COLOR_PINK		{255,20,147,3}
#define RGBA_COLOR_MAROON	{128,0,0,3}
#define RGBA_COLOR_SKYBLUE	{135,206,25,3}
#define RGBA_COLOR_GOLD		{255,215,0,3}
#define RGBA_COLOR_BROWN	{139,69,19,3}
#define RGBA_COLOR_VIOLET	{238,130,238,3}
#endif

#if !defined FFADE_IN
// The following are from the SourceSDK, used for the optional flags field of War3_FlashScreen
#define FFADE_IN			0x0001		// Just here so we don't pass 0 into the function, YOUR SCREEN DECAYS AND YOU SEE CLEARLY SLOWLY
#define FFADE_OUT			0x0002		// Fade out (not in)
#define FFADE_MODULATE		0x0004		// Modulate (don't blend)
#define FFADE_STAYOUT		0x0008		// ignores the duration, stays faded out until new ScreenFade message received
#define FFADE_PURGE			0x0010		// Purges all other fades, replacing them with this one
#endif



#define  TEAM_T 2
#define  TEAM_CT 3
#define  TEAM_RED 2
#define  TEAM_BLUE 3


