#include "bot_ai.h"


uint32 conflagarate_cd;
uint32 chaos_bolt_cd;

#define CONFLAGRATE_CD  100
#define CHAOS_BOLT_CD   120
#define RAIN_OF_FIRE_CD 300

#define PET_VOIDWALKER 697

//Curses
#define CURSE_OF_THE_ELEMENTS SPELL_CURSE_OF_THE_ELEMENTS_A[SPELL_LEVEL]

//DESTRUCTION
#define SHADOW_BOLT         SPELL_SHADOW_BOLT_A[SPELL_LEVEL]
#define IMMOLATE            SPELL_IMMOLATE_A[SPELL_LEVEL]
#define CONFLAGRATE         SPELL_CONFLAGRATE_A[SPELL_LEVEL]
#define CHAOS_BOLT          SPELL_CHAOS_BOLT_A[SPELL_LEVEL]
#define RAIN_OF_FIRE        SPELL_RAIN_OF_FIRE_A[SPELL_LEVEL]

//AFFLICTION
#define HAUNT               SPELL_HAUNT_A[SPELL_LEVEL]
#define CORRUPTION          SPELL_CORRUPTION_A[SPELL_LEVEL]
#define UNSTABLE_AFFLICTION SPELL_UNSTABLE_AFFLICTION_A[SPELL_LEVEL]

//curses
uint32 SPELL_CURSE_OF_THE_ELEMENTS_A[] = { 0, 0, 0, 1490, 11721, 11721, 11722, 27728, 47865 };

//destruction spells
uint32 SPELL_SHADOW_BOLT_A[] = { 686, 705, 1088, 7641, 11659, 11660, 25307, 47808, 47809 };
uint32 SPELL_IMMOLATE_A[] = { 348, 707, 1094, 2941, 11665, 11667, 25309, 47810, 47811 };
uint32 SPELL_CONFLAGRATE_A[] = { 0, 0, 0, 0, 17962, 17962, 17962, 17962, 17962 };
uint32 SPELL_CHAOS_BOLT_A[] = { 0, 0, 0, 0, 0, 50796, 50796, 50796, 50796 };
uint32 SPELL_RAIN_OF_FIRE_A[] = { 0, 0, 5740, 6219, 11677, 11678, 11678, 27212, 27212 };

//affliction spells
uint32 SPELL_HAUNT_A[] = { 0, 0, 0, 0, 0, 0, 59164, 59164, 59164 };
uint32 SPELL_CORRUPTION_A[] = { 172, 6222, 7648, 11671, 11672, 25311, 47812, 47835, 47836 };
uint32 SPELL_UNSTABLE_AFFLICTION_A[] = { 0, 0, 0, 0, 0, 30404, 30405, 47843,  47843 };

