#include "crt.h"
#include "logs.h"

#pragma once

#define maptbl(t, id) (t[imax(0, imin(id, (int)(sizeof(t)/sizeof(t[0]))))])

enum class_s : unsigned char {
	Cleric, Fighter, Mage, Theif,
	FirstClass = Cleric, LastClass = Theif,
};
enum race_s : unsigned char {
	NoRace,
	Dwarf, Elf, Halfling, Human,
	Animal, Beastman, Construct, FantasticCreature,
	GiantHumanoid, Ooze, SummonedCreature,
	Undead, Vermin
};
enum ability_s : unsigned char {
	Strenght, Dexterity, Constitution, Intellegence, Wisdow, Charisma
};
enum alignment_s : unsigned char {
	Lawful, Neutral, Chaotic
};
enum gender_s : unsigned char {
	Male, Female,
};
enum save_s : unsigned char {
	NoSave,
	SavePetrification, SaveParalizis, SavePoison, SaveDeath,
	SaveBlast, SaveBreath, SaveStaffWands, SaveSpells
};
enum proficiency_s : unsigned char {
	Acrobatics, Alchemy, Alertness, Ambushing, AnimalHusbandry, AnimalTraining, Apostasy, ArcaneDabblin, Painting,
	Bargaining, BattleMagic, BeastFriendship, Berserkergang, BlackLoreOfZahar, BlindFighting, Bribery,
	Caving, CatBurglary, Climbing, CollegiateWizardry, CombatReflexes, CombatTrickery, Command, Contemplation, Contortionism,
	Smithing,
	Diplomacy, Disguise, DivineBlessing, DivineHealth, DungeonBashing, DwarvenBrewing,
	Eavesdropping, Elementalism, Endurance, Engineering,
	Familiar, FightingStyleDualWeapon, FightingStyleMissile, FightingStylePole, FightingStyleSigle, FightingStyleTwoHanded, FightingStyleWeaponAndShield,
	Gambling, GoblinSlaying,
	Healing,
	IllusionResistance, Intimidation,
	History, Mining, LandSurveying, LayingOnHands, Leadership, LipReading, Lockpicking, Loremastery,
	MagicalMusic, Mapping, MartialTraining, MilitaryStrategy, Mimicry, Mountaineering, MysticAura,
	Naturalism, Navigation,
	PassingWithoutTrace, Dancing, PreciseShooting, Prestidigitation, Scribing, Prophecy,
	QuietMagic,
	Riding, RighteousTurning, Running,
	Seafaring, Seduction, SensingEvil, SensingPower, Signaling, Skirmishing, Skulking, Sniping, Survival, Swashbuckling,
	Theology, TrapFinding, Tracking, Transmogrification, Trapping,
	WeaponFinesse, WeaponFocusBows, WeaponFocusSwords, WeaponFocusAxes,
	FirstSkill = Acrobatics, LastSkill = WeaponFocusAxes,
};
enum language_s : unsigned char {
	LanguageDwarvish, LanguageElvish, LanguageGiant, LanguageGoblin, LanguageHalfling, LanguageOrc,
	LanguageAbysal, LanguageCelestial, LanguageDraconic, LanguageDeepSpeech,
	FirstLanguage = LanguageDwarvish, LastLanguage = LanguageDeepSpeech
};
enum state_s : unsigned char {
	StateBlessed, StateCharmed, StateLighted, StateProtectedFromEvil, StateShielded, StateSleeped,
	FirstState = StateBlessed, LastState = StateSleeped,
};
enum building_s : unsigned char {
	Barracs, Castle, Graveyard, Harbor, Laboratory,
	Marketplace, Mill, Stable, Smithy, Tavern,
	Temple,
	FirstBuilding = Barracs, LastBuilding = Temple,
};
enum item_s : unsigned char {
	NoItem,
	// Items (weapon melee)
	Club, Flail, Hammer, Mace,
	Spear, Javelin, Staff,
	Axe, Halberd,
	Dagger, SwordGreat, SwordLong, SwordShort,
	// Items (weapon ranged)
	Crossbow, BowLong, BowShort, Dart, Sling,
	Stone, Arrow, Bolt,
	// Items (armor)
	PaddedArmour, LeatherArmour, StuddedLeatherArmour,
	HideArmour, ChainShirt, ScaleMail, BreastPlate, HalfPlate,
	RingMail, ChainMail, SplintMail, PlateMail,
	Shield, Helmet, Bracers,
	// Items (other)
	Ration, Apple, BreadHalflings, BreadEvlen, BreadDwarven, Cake, Sausage, Meat,
	Coin,
	FirstItem = Club, LastItem = Coin,
};
enum wear_s : unsigned char {
	// Body locations
	MeleeWeapon, SecondanaryWeapon, RangedWeapon,
	Head, Neck, Torso, Amunitions, RightFinger, LeftFinger, Elbows, Legs,
	FirstWear = MeleeWeapon, LastBodyLocation = Legs
};
enum size_s : unsigned char {
	SizeTiny, SizeSmall, SizeMedium, SizeLarge, SizeHuge
};
enum range_s : unsigned char {
	RangeSelf, RangeTouch, Range10, Range30, Range60, Range120, Range150, Range240
};
enum duration_s : unsigned char {
	TimeInstantaneous, TimeConcentration, TimeSpecial,
	Time2Turns, Time3Turns, Time4d4Turns, Time6p1Turns, Time2d6Turns,
	Time6Turns,
};
enum spell_s : unsigned char {
	SpellCharmPerson, SpellDetectMagic, SpellFloatingDisc, SpellHoldPortal, SpellLight,
	SpellMagicMissile, SpellMagicMouth, SpellProtectionFromEvil, SpellReadLanguages, SpellShield,
	SpellSleep, SpellVentriloquism,
	SpellContinualLight,
	FirstSpell = SpellCharmPerson, LastSpell = SpellContinualLight,
};
enum monster_s : unsigned char {
	Ork, Zombie,
	FirstMonster = Ork, LastMonster = Zombie,
};
struct hero
{
	race_s				race;
	gender_s			gender;
	class_s				type;
	char				level;
	alignment_s			alignment;
	const char*			getname();
private:
	unsigned char		name;
};