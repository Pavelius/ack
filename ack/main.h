#include "adat.h"
#include "crt.h"
#include "logs.h"

#pragma once

#define assert_enum(name, last) static_assert(sizeof(name##_data) / sizeof(name##_data[0]) == last + 1,\
	"Invalid count of " #name " elements")
#define getstr_enum(ename) template<> const char* getstr<ename##_s>(ename##_s value) { return ename##_data[value].name[1]; }
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
enum skill_s : unsigned char {
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
struct item
{
	item_s				type;
	bool				islight() const;
	bool				istwohanded() const;
};
struct hero
{
	race_s				race;
	gender_s			gender;
	class_s				type;
	char				level;
	alignment_s			alignment;
	short				hp;
	//
	void				add(skill_s id, int value) { proficiency[id] += value; }
	void				chooseability();
	void				chooseclass(bool interactive);
	void				choosegender(bool interactive);
	void				chooseskills(bool interactive, const char* skill_name, skill_s* source, unsigned maximum, int count = 1);
	void				clear();
	static hero*		create(bool interactive);
	int					get(ability_s id) const { return ability[id]; }
	int					get(skill_s id) const { return proficiency[id]; }
	int					getbonus(ability_s id) const;
	const char*			getname() const;
	int					getmaxhp() const;
	int					getprepared(skill_s id) const { return spell_prepared[id]; }
	int					getprogress() const { return 4; }
	void				levelup(bool interactive);
	void				setprepared(skill_s id, int value) { spell_prepared[id] = (unsigned char)value; }
private:
	short				mhp;
	unsigned char		ability[Charisma + 1];
	unsigned char		proficiency[LastSkill + 1];
	unsigned char		spell_prepared[LastSkill + 1];
	unsigned char		name;
};
namespace game
{
	int					getdice(class_s id);
	unsigned char*		getminimal(class_s id);
	ability_s			getprime(class_s id);
}
extern adat<hero, 260>	heroes;