#pragma once

#define OFFSET_ENTITYLIST 0x19fbc18 //cl_entitylist
#define OFFSET_LOCAL_ENT 0x1dac9c8 //LocalPlayer
#define OFFSET_HEALTH 0x0438 //m_iHealth
#define OFFSET_SHIELD 0x0170 //m_shieldHealth
#define OFFSET_SHIELD_MAX 0x0174 //m_shieldHealthMax
#define OFFSET_ORIGIN 0x014c //m_vecAbsOrigin
#define OFFSET_BONES 0x0f38 //m_bConstrainBetweenEndpoints
#define OFFSET_MATRIX 0x11a210 //ViewMatrix
#define OFFSET_RENDER 0x7519720 //ViewRender
#define OFFSET_NAMELIST 0xb9f7e40 //NameList
#define OFFSET_NAME    0x0589 //m_iName
#define OFFSET_VIEWANGLES 0x2588 //m_ammoPoolCapacity - 0x14
#define OFFSET_BREATH_ANGLES (OFFSET_VIEWANGLES - 0x10)
#define OFFSET_CAMERAPOS 0x1f40 //CPlayer!camera_origin
#define OFFSET_TEAM    0x0448 //m_iTeamNum
#define OFFSET_BLEED_OUT_STATE 0x2728 //m_bleedoutState
#define OFFSET_VISIBLE_TIME 0x1b14 //CPlayer!lastVisibleTime
#define OFFSET_MODELNAME 0x0030 //m_ModelName=0x0030
#define OFFSET_AIMPUNCH    0x24a0 //m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle
#define OFFSET_CURRENT_WEAPON 0x1aac //m_latestPrimaryWeapons
#define OFFSET_BULLET_SPEED    0x1f40 //CWeaponX!m_flProjectileSpeed
#define OFFSET_BULLET_SCALE 0x1f48 //CWeaponX!m_flProjectileScale
#define OFFSET_BULLET_GRAVITY (OFFSET_BULLET_SPEED + 0x8)
#define OFFSET_THIRDPERSON 0x019e0740 + 0x6c //thirdperson_override + 0x6c
#define OFFSET_SKIN 0x0ea8 //m_nSkin
#define OFFSET_TIMESCALE 0x013d85c0 //host_timescale
#define OFFSET_AMMO 0x16b4 //m_ammoInClip
#define OFFSET_VIEWMODEL 0x2d4c //m_hViewModels
#define OFFSET_LIFE_STATE 0x0798 //m_lifeState
#define OFFSET_ITEM_ID 0x16b8 //m_customScriptInt
#define OFFSET_OBSERVERMODE 0x34cc //m_iObserverMode
#define OFFSET_MUTEWEAPONSOUND 0x01f39010 + 0x6B //muteWeaponSounds + 0x6B
#define OFFSET_ITEM_GLOW 0x2c0 //m_highlightFunctionBits
#define OFFSET_NETCHAN 0x01350e50 //netchan_addr
#define OFFSET_NETCHAN_SENDPACKET 0x118 //???UNKNOWN
#define OFFSET_FORCE_JUMP 0x07519868 + 0x08 //in_jump + 0x08
#define OFFSET_FORCE_ATTACK 0x075197f0 + 0x08 //in_attack + 0x08
#define OFFSET_FORCE_DUCK 0x0b9f8888 + 0x08 //in_duck + 0x08

#define GLOW_FADE 0x388
#define GLOW_DISTANCE 0x3B4
#define GLOW_CONTEXT 0x3C8
#define GLOW_LIFE_TIME 0x3A4
#define GLOW_VISIBLE_TYPE 0x3D0
#define GLOW_TYPE 0x2C4
#define GLOW_COLOR 0x1D0
#define GLOW_COLOR2 0x1D4 // GLOW_COLOR + 0x4
#define GLOW_COLOR3 0x1D8 // GLOW_COLOR + 0x8