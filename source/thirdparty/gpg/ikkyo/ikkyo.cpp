/*
Copyright (C) 2003-2004 Jason 'Ikkyo' Gripp.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

// ikkyo.dsdll
// email: jgripp@budget.net
// Version 1.5.6

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include "dsdll.h"
#include "gpstring_std.h"

using namespace std;

#ifdef LOA
#define OFFSET_OPEN_SPELLBOOK	0x28
#else
#define OFFSET_OPEN_SPELLBOOK	0x27
#endif

void DumpMemoryBytes(FILE *pFile, void *mem, int len, int depth)
{
	BYTE *data = (BYTE *)mem;

	for (int i = 0; i < len; i += 32)
	{
		if (!IsBadReadPtr(data + i, 32))
		{

			fprintf(pFile, 
				"%i - %08x  %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
				depth,
				DWORD(mem) + i,
				data[i], data[i+1], data[i+2], data[i+3],
				data[i+4], data[i+5], data[i+6], data[i+7],
				data[i+8], data[i+9], data[i+10], data[i+11],
				data[i+12], data[i+13], data[i+14], data[i+15],
				data[i+16], data[i+17], data[i+18], data[i+19],
				data[i+20], data[i+21], data[i+22], data[i+23],
				data[i+24], data[i+25], data[i+26], data[i+27],
				data[i+28], data[i+29], data[i+30], data[i+31],
				isprint(data[i]) ? data[i] : '.',
				isprint(data[i+1]) ? data[i+1] : '.',
				isprint(data[i+2]) ? data[i+2] : '.',
				isprint(data[i+3]) ? data[i+3] : '.',
				isprint(data[i+4]) ? data[i+4] : '.',
				isprint(data[i+5]) ? data[i+5] : '.',
				isprint(data[i+6]) ? data[i+6] : '.',
				isprint(data[i+7]) ? data[i+7] : '.',
				isprint(data[i+8]) ? data[i+8] : '.',
				isprint(data[i+9]) ? data[i+9] : '.',
				isprint(data[i+10]) ? data[i+10] : '.',
				isprint(data[i+11]) ? data[i+11] : '.',
				isprint(data[i+12]) ? data[i+12] : '.',
				isprint(data[i+13]) ? data[i+13] : '.',
				isprint(data[i+14]) ? data[i+14] : '.',
				isprint(data[i+15]) ? data[i+15] : '.',
				isprint(data[i+16]) ? data[i+16] : '.',
				isprint(data[i+17]) ? data[i+17] : '.',
				isprint(data[i+18]) ? data[i+18] : '.',
				isprint(data[i+19]) ? data[i+19] : '.',
				isprint(data[i+20]) ? data[i+20] : '.',
				isprint(data[i+21]) ? data[i+21] : '.',
				isprint(data[i+22]) ? data[i+22] : '.',
				isprint(data[i+23]) ? data[i+23] : '.',
				isprint(data[i+24]) ? data[i+24] : '.',
				isprint(data[i+25]) ? data[i+25] : '.',
				isprint(data[i+26]) ? data[i+26] : '.',
				isprint(data[i+27]) ? data[i+27] : '.',
				isprint(data[i+28]) ? data[i+28] : '.',
				isprint(data[i+29]) ? data[i+29] : '.',
				isprint(data[i+30]) ? data[i+30] : '.',
				isprint(data[i+31]) ? data[i+31] : '.'
			);
		}
		else if (!IsBadReadPtr(data + i, 16))
		{
			fprintf(pFile, 
				"%i - %08x  %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
				depth,
				DWORD(mem) + i,
				data[i], data[i+1], data[i+2], data[i+3],
				data[i+4], data[i+5], data[i+6], data[i+7],
				data[i+8], data[i+9], data[i+10], data[i+11],
				data[i+12], data[i+13], data[i+14], data[i+15],
				isprint(data[i]) ? data[i] : '.',
				isprint(data[i+1]) ? data[i+1] : '.',
				isprint(data[i+2]) ? data[i+2] : '.',
				isprint(data[i+3]) ? data[i+3] : '.',
				isprint(data[i+4]) ? data[i+4] : '.',
				isprint(data[i+5]) ? data[i+5] : '.',
				isprint(data[i+6]) ? data[i+6] : '.',
				isprint(data[i+7]) ? data[i+7] : '.',
				isprint(data[i+8]) ? data[i+8] : '.',
				isprint(data[i+9]) ? data[i+9] : '.',
				isprint(data[i+10]) ? data[i+10] : '.',
				isprint(data[i+11]) ? data[i+11] : '.',
				isprint(data[i+12]) ? data[i+12] : '.',
				isprint(data[i+13]) ? data[i+13] : '.',
				isprint(data[i+14]) ? data[i+14] : '.',
				isprint(data[i+15]) ? data[i+15] : '.'
			);
		}
		else if (!IsBadReadPtr(data + i, 8))
		{
			fprintf(pFile, 
				"%i - %08x  %02x %02x %02x %02x %02x %02x %02x %02x  %c%c%c%c%c%c%c%c\n",
				depth,
				DWORD(mem) + i,
				data[i], data[i+1], data[i+2], data[i+3],
				data[i+4], data[i+5], data[i+6], data[i+7],
				isprint(data[i]) ? data[i] : '.',
				isprint(data[i+1]) ? data[i+1] : '.',
				isprint(data[i+2]) ? data[i+2] : '.',
				isprint(data[i+3]) ? data[i+3] : '.',
				isprint(data[i+4]) ? data[i+4] : '.',
				isprint(data[i+5]) ? data[i+5] : '.',
				isprint(data[i+6]) ? data[i+6] : '.',
				isprint(data[i+7]) ? data[i+7] : '.'
			);
		}
		else if (!IsBadReadPtr(data + i, 4))
		{
			fprintf(pFile, 
				"%i - %08x  %02x %02x %02x %02x  %c%c%c%c\n",
				depth,
				DWORD(mem) + i,
				data[i], data[i+1], data[i+2], data[i+3],
				isprint(data[i]) ? data[i] : '.',
				isprint(data[i+1]) ? data[i+1] : '.',
				isprint(data[i+2]) ? data[i+2] : '.',
				isprint(data[i+3]) ? data[i+3] : '.'
			);
		}
		else
			return;
	}

	fprintf(pFile, "\n");

	if (depth > 0)
	{
		DWORD *dwData = (DWORD *)mem;

		for (int i = 0; i < len/sizeof(DWORD); i++)
		{
			DumpMemoryBytes(pFile, (void *)dwData[i], 64, depth - 1);
		}
	}
}

void DumpMemoryDwords(FILE *pFile, void *mem, int len, int depth)
{
	DWORD *data = (DWORD *)mem;
	BYTE *bdata = (BYTE *)mem;

	for (int i = 0; i < len; i += 8)
	{
		if (!IsBadReadPtr(data + i, sizeof(DWORD) * 8))
		{
			fprintf(pFile, 
				"%i - %08x  %08x %08x %08x %08x %08x %08x %08x %08x  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
				depth,
				DWORD(mem) + i,
				data[i], data[i+1], data[i+2], data[i+3],
				data[i+4], data[i+5], data[i+6], data[i+7],
				isprint(bdata[i*4]) ? bdata[i*4] : '.',
				isprint(bdata[i*4+1]) ? bdata[i*4+1] : '.',
				isprint(bdata[i*4+2]) ? bdata[i*4+2] : '.',
				isprint(bdata[i*4+3]) ? bdata[i*4+3] : '.',
				isprint(bdata[i*4+4]) ? bdata[i*4+4] : '.',
				isprint(bdata[i*4+5]) ? bdata[i*4+5] : '.',
				isprint(bdata[i*4+6]) ? bdata[i*4+6] : '.',
				isprint(bdata[i*4+7]) ? bdata[i*4+7] : '.',
				isprint(bdata[i*4+8]) ? bdata[i*4+8] : '.',
				isprint(bdata[i*4+9]) ? bdata[i*4+9] : '.',
				isprint(bdata[i*4+10]) ? bdata[i*4+10] : '.',
				isprint(bdata[i*4+11]) ? bdata[i*4+11] : '.',
				isprint(bdata[i*4+12]) ? bdata[i*4+12] : '.',
				isprint(bdata[i*4+13]) ? bdata[i*4+13] : '.',
				isprint(bdata[i*4+14]) ? bdata[i*4+14] : '.',
				isprint(bdata[i*4+15]) ? bdata[i*4+15] : '.',
				isprint(bdata[i*4+16]) ? bdata[i*4+16] : '.',
				isprint(bdata[i*4+17]) ? bdata[i*4+17] : '.',
				isprint(bdata[i*4+18]) ? bdata[i*4+18] : '.',
				isprint(bdata[i*4+19]) ? bdata[i*4+19] : '.',
				isprint(bdata[i*4+20]) ? bdata[i*4+20] : '.',
				isprint(bdata[i*4+21]) ? bdata[i*4+21] : '.',
				isprint(bdata[i*4+22]) ? bdata[i*4+22] : '.',
				isprint(bdata[i*4+23]) ? bdata[i*4+23] : '.',
				isprint(bdata[i*4+24]) ? bdata[i*4+24] : '.',
				isprint(bdata[i*4+25]) ? bdata[i*4+25] : '.',
				isprint(bdata[i*4+26]) ? bdata[i*4+26] : '.',
				isprint(bdata[i*4+27]) ? bdata[i*4+27] : '.',
				isprint(bdata[i*4+28]) ? bdata[i*4+28] : '.',
				isprint(bdata[i*4+29]) ? bdata[i*4+29] : '.',
				isprint(bdata[i*4+30]) ? bdata[i*4+30] : '.',
				isprint(bdata[i*4+31]) ? bdata[i*4+31] : '.'
			);
		}
		else if (!IsBadReadPtr(data + i, sizeof(DWORD) * 4))
		{
			fprintf(pFile, 
				"%i - %08x  %08x %08x %08x %08x  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
				depth,
				DWORD(mem) + i,
				data[i], data[i+1], data[i+2], data[i+3],
				isprint(bdata[i*4]) ? bdata[i*4] : '.',
				isprint(bdata[i*4+1]) ? bdata[i*4+1] : '.',
				isprint(bdata[i*4+2]) ? bdata[i*4+2] : '.',
				isprint(bdata[i*4+3]) ? bdata[i*4+3] : '.',
				isprint(bdata[i*4+4]) ? bdata[i*4+4] : '.',
				isprint(bdata[i*4+5]) ? bdata[i*4+5] : '.',
				isprint(bdata[i*4+6]) ? bdata[i*4+6] : '.',
				isprint(bdata[i*4+7]) ? bdata[i*4+7] : '.',
				isprint(bdata[i*4+8]) ? bdata[i*4+8] : '.',
				isprint(bdata[i*4+9]) ? bdata[i*4+9] : '.',
				isprint(bdata[i*4+10]) ? bdata[i*4+10] : '.',
				isprint(bdata[i*4+11]) ? bdata[i*4+11] : '.',
				isprint(bdata[i*4+12]) ? bdata[i*4+12] : '.',
				isprint(bdata[i*4+13]) ? bdata[i*4+13] : '.',
				isprint(bdata[i*4+14]) ? bdata[i*4+14] : '.',
				isprint(bdata[i*4+15]) ? bdata[i*4+15] : '.'
			);
		}
		else if (!IsBadReadPtr(data + i, sizeof(DWORD) * 2))
		{
			fprintf(pFile, 
				"%i - %08x  %08x %08x  %c%c%c%c%c%c%c%c\n",
				depth,
				DWORD(mem) + i,
				data[i], data[i+1],
				isprint(bdata[i*4]) ? bdata[i*4] : '.',
				isprint(bdata[i*4+1]) ? bdata[i*4+1] : '.',
				isprint(bdata[i*4+2]) ? bdata[i*4+2] : '.',
				isprint(bdata[i*4+3]) ? bdata[i*4+3] : '.',
				isprint(bdata[i*4+4]) ? bdata[i*4+4] : '.',
				isprint(bdata[i*4+5]) ? bdata[i*4+5] : '.',
				isprint(bdata[i*4+6]) ? bdata[i*4+6] : '.',
				isprint(bdata[i*4+7]) ? bdata[i*4+7] : '.'
			);
		}
		else if (!IsBadReadPtr(data + i, sizeof(DWORD)))
		{
			fprintf(pFile, 
				"%i - %08x  %08x  %c%c%c%c\n",
				depth,
				DWORD(mem) + i,
				data[i],
				isprint(bdata[i*4]) ? bdata[i*4] : '.',
				isprint(bdata[i*4+1]) ? bdata[i*4+1] : '.',
				isprint(bdata[i*4+2]) ? bdata[i*4+2] : '.',
				isprint(bdata[i*4+3]) ? bdata[i*4+3] : '.'
			);
		}
		else
			return;
	}

	fprintf(pFile, "\n");

	if (depth > 0)
	{
		DWORD *dwData = (DWORD *)mem;

		for (int i = 0; i < len/sizeof(DWORD); i++)
		{
			DumpMemoryDwords(pFile, (void *)dwData[i], 64, depth - 1);
		}
	}
}

void DumpMemoryFloats(FILE *pFile, void *mem, int len, int depth)
{
	float *data = (float *)mem;
	BYTE *bdata = (BYTE *)mem;

	for (int i = 0; i < len; i += 8)
	{
		if (!IsBadReadPtr(data + i, sizeof(float) * 8))
		{
			fprintf(pFile, 
				"%i - %08x  %8f %8f %8f %8f %8f %8f %8f %8f  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
				depth,
				DWORD(mem) + i,
				data[i], data[i+1], data[i+2], data[i+3],
				data[i+4], data[i+5], data[i+6], data[i+7],
				isprint(bdata[i*4]) ? bdata[i*4] : '.',
				isprint(bdata[i*4+1]) ? bdata[i*4+1] : '.',
				isprint(bdata[i*4+2]) ? bdata[i*4+2] : '.',
				isprint(bdata[i*4+3]) ? bdata[i*4+3] : '.',
				isprint(bdata[i*4+4]) ? bdata[i*4+4] : '.',
				isprint(bdata[i*4+5]) ? bdata[i*4+5] : '.',
				isprint(bdata[i*4+6]) ? bdata[i*4+6] : '.',
				isprint(bdata[i*4+7]) ? bdata[i*4+7] : '.',
				isprint(bdata[i*4+8]) ? bdata[i*4+8] : '.',
				isprint(bdata[i*4+9]) ? bdata[i*4+9] : '.',
				isprint(bdata[i*4+10]) ? bdata[i*4+10] : '.',
				isprint(bdata[i*4+11]) ? bdata[i*4+11] : '.',
				isprint(bdata[i*4+12]) ? bdata[i*4+12] : '.',
				isprint(bdata[i*4+13]) ? bdata[i*4+13] : '.',
				isprint(bdata[i*4+14]) ? bdata[i*4+14] : '.',
				isprint(bdata[i*4+15]) ? bdata[i*4+15] : '.',
				isprint(bdata[i*4+16]) ? bdata[i*4+16] : '.',
				isprint(bdata[i*4+17]) ? bdata[i*4+17] : '.',
				isprint(bdata[i*4+18]) ? bdata[i*4+18] : '.',
				isprint(bdata[i*4+19]) ? bdata[i*4+19] : '.',
				isprint(bdata[i*4+20]) ? bdata[i*4+20] : '.',
				isprint(bdata[i*4+21]) ? bdata[i*4+21] : '.',
				isprint(bdata[i*4+22]) ? bdata[i*4+22] : '.',
				isprint(bdata[i*4+23]) ? bdata[i*4+23] : '.',
				isprint(bdata[i*4+24]) ? bdata[i*4+24] : '.',
				isprint(bdata[i*4+25]) ? bdata[i*4+25] : '.',
				isprint(bdata[i*4+26]) ? bdata[i*4+26] : '.',
				isprint(bdata[i*4+27]) ? bdata[i*4+27] : '.',
				isprint(bdata[i*4+28]) ? bdata[i*4+28] : '.',
				isprint(bdata[i*4+29]) ? bdata[i*4+29] : '.',
				isprint(bdata[i*4+30]) ? bdata[i*4+30] : '.',
				isprint(bdata[i*4+31]) ? bdata[i*4+31] : '.'
			);
		}
		else if (!IsBadReadPtr(data + i, sizeof(float) * 4))
		{
			fprintf(pFile, 
				"%i - %08x  %8f %8f %8f %8f  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
				depth,
				DWORD(mem) + i,
				data[i], data[i+1], data[i+2], data[i+3],
				isprint(bdata[i*4]) ? bdata[i*4] : '.',
				isprint(bdata[i*4+1]) ? bdata[i*4+1] : '.',
				isprint(bdata[i*4+2]) ? bdata[i*4+2] : '.',
				isprint(bdata[i*4+3]) ? bdata[i*4+3] : '.',
				isprint(bdata[i*4+4]) ? bdata[i*4+4] : '.',
				isprint(bdata[i*4+5]) ? bdata[i*4+5] : '.',
				isprint(bdata[i*4+6]) ? bdata[i*4+6] : '.',
				isprint(bdata[i*4+7]) ? bdata[i*4+7] : '.',
				isprint(bdata[i*4+8]) ? bdata[i*4+8] : '.',
				isprint(bdata[i*4+9]) ? bdata[i*4+9] : '.',
				isprint(bdata[i*4+10]) ? bdata[i*4+10] : '.',
				isprint(bdata[i*4+11]) ? bdata[i*4+11] : '.',
				isprint(bdata[i*4+12]) ? bdata[i*4+12] : '.',
				isprint(bdata[i*4+13]) ? bdata[i*4+13] : '.',
				isprint(bdata[i*4+14]) ? bdata[i*4+14] : '.',
				isprint(bdata[i*4+15]) ? bdata[i*4+15] : '.'
			);
		}
		else if (!IsBadReadPtr(data + i, sizeof(float) * 2))
		{
			fprintf(pFile, 
				"%i - %08x  %8f %8f  %c%c%c%c%c%c%c%c\n",
				depth,
				DWORD(mem) + i,
				data[i], data[i+1],
				isprint(bdata[i*4]) ? bdata[i*4] : '.',
				isprint(bdata[i*4+1]) ? bdata[i*4+1] : '.',
				isprint(bdata[i*4+2]) ? bdata[i*4+2] : '.',
				isprint(bdata[i*4+3]) ? bdata[i*4+3] : '.',
				isprint(bdata[i*4+4]) ? bdata[i*4+4] : '.',
				isprint(bdata[i*4+5]) ? bdata[i*4+5] : '.',
				isprint(bdata[i*4+6]) ? bdata[i*4+6] : '.',
				isprint(bdata[i*4+7]) ? bdata[i*4+7] : '.'
			);
		}
		else if (!IsBadReadPtr(data + i, sizeof(float)))
		{
			fprintf(pFile, 
				"%i - %08x  %8f  %c%c%c%c\n",
				depth,
				DWORD(mem) + i,
				data[i],
				isprint(bdata[i*4]) ? bdata[i*4] : '.',
				isprint(bdata[i*4+1]) ? bdata[i*4+1] : '.',
				isprint(bdata[i*4+2]) ? bdata[i*4+2] : '.',
				isprint(bdata[i*4+3]) ? bdata[i*4+3] : '.'
			);
		}
		else
			return;
	}

	fprintf(pFile, "\n");

	if (depth > 0)
	{
		DWORD *dwData = (DWORD *)mem;

		for (int i = 0; i < len/sizeof(float); i++)
		{
			DumpMemoryFloats(pFile, (void *)dwData[i], 64, depth - 1);
		}
	}
}

enum eInventoryLocation
{
	IL_ACTIVE_MELEE_WEAPON = 0,
	IL_ACTIVE_RANGED_WEAPON,
	IL_ACTIVE_PRIMARY_SPELL,
	IL_ACTIVE_SECONDARY_SPELL,
	IL_SPELL_1,
	IL_SPELL_2,
	IL_SPELL_3,
	IL_SPELL_4,
	IL_SPELL_5,
	IL_SPELL_6,
	IL_SPELL_7,
	IL_SPELL_8,
	IL_SPELL_9,
	IL_SPELL_10,
	IL_SPELL_11,
	IL_SPELL_12,
	IL_SHIELD,
	IL_INVALID,
	IL_ALL,
	IL_ALL_ACTIVE,
	IL_ALL_SPELLS,
	IL_MAIN,
};

FEX eInventoryLocation MakeInventoryLocation( int il )
{
	return (eInventoryLocation)il;
}

enum ePlayerSkin
{
	PS_FLESH = 0,
	PS_CLOTH,
};

FEX ePlayerSkin MakePlayerSkin( int ps )
{
	return (ePlayerSkin)ps;
}

enum eEquipSlot
{
	ES_SHIELD_HAND = 0,
	ES_WEAPON_HAND,
	ES_FEET,
	ES_CHEST,
	ES_HEAD,
	ES_FOREARMS,
	ES_AMULET,
	ES_SPELLBOOK,
	ES_RING_0,
	ES_RING_1,
	ES_RING_2,
	ES_RING_3,
	ES_RING,
	ES_NONE,
	ES_ANY,
};

FEX eEquipSlot MakeEquipSlot( int es )
{
	return (eEquipSlot)es;
}

FEX DWORD MakeToolTipColor( const char *tooltip_color_name )
{
	if(!strcmp(tooltip_color_name, "nature_magic"))
	{
		return 0xff43ca83;
	}
	else if(!strcmp(tooltip_color_name, "combat_magic"))
	{
		return 0xffeaa935;
	}
	else if(!strcmp(tooltip_color_name, "ranged_magic"))
	{
		return 0xffcaca43;
	}
	else if(!strcmp(tooltip_color_name, "melee_magic"))
	{
		return 0xffca43c8;
	}

	return 0xffffffff;
}

// Temporary space used for returning strings
static char		buffer[256];

class GRect
{
	FEX int GetLeft() const
	{		
		return ((RECT*)this)->left;
	}

	FEX int GetTop() const
	{		
		return ((RECT*)this)->top;
	}

	FEX int GetRight() const
	{		
		return ((RECT*)this)->right;
	}

	FEX int GetBottom() const
	{		
		return ((RECT*)this)->bottom;
	}

	FEX void SetLeft( int left )
	{		
		((RECT*)this)->left = left;
	}

	FEX void SetTop( int top )
	{		
		((RECT*)this)->top = top;
	}

	FEX void SetRight( int right )
	{		
		((RECT*)this)->right = right;
	}

	FEX void SetBottom( int bottom )
	{		
		((RECT*)this)->bottom = bottom;
	}
};

struct ComplexLine
{
	DWORD color;
	const wchar_t *text;
	DWORD unknown2;
	DWORD unknown3;
};

struct TextboxLine
{
	DWORD color;
	const wchar_t *text;
	DWORD unknown1;
	DWORD unknown2;
	ComplexLine *startComplex;
	ComplexLine *endComplex;
	DWORD unknown3;
};



class UITextBox
{
	FEX const char* GetLineText( int line ) const
	{
		DWORD *addr = (DWORD *) this;
		TextboxLine *linePointer = 	(TextboxLine*)(addr[0x6a]);
		TextboxLine *linePointerEnd	= (TextboxLine*)(addr[0x6b]);
		int numLines = linePointerEnd-linePointer;

		if(!linePointer || line >= numLines || line < 0)
			return "";
		
		linePointer += line;

		if(linePointer->text)
		{
			sprintf(buffer, "%S", linePointer->text);
		}
		else
		{
			buffer[0] = '\0';
		}

		return buffer;
	}

	FEX DWORD GetLineColor( int line ) const
	{
		DWORD *addr = (DWORD *) this;
		TextboxLine *linePointer = 	(TextboxLine*)(addr[0x6a]);
		TextboxLine *linePointerEnd	= (TextboxLine*)(addr[0x6b]);
		int numLines = linePointerEnd-linePointer;

		if(!linePointer || line >= numLines || line < 0)
			return 0x00000000;
		
		linePointer += line;

		return linePointer->color;
	}

	FEX void SetLineColor( int line, DWORD color )
	{
		DWORD *addr = (DWORD *) this;
		TextboxLine *linePointer = (TextboxLine*)(addr[0x6a]);
		TextboxLine *linePointerEnd	= (TextboxLine*)(addr[0x6b]);
		int numLines = linePointerEnd-linePointer;

		if(!linePointer || line >= numLines || line < 0)
			return;
		
		linePointer += line;

		linePointer->color = color;
	}

	FEX int FindLine( const char* text ) const
	{
		DWORD *addr = (DWORD *) this;
		TextboxLine *linePointer		=	(TextboxLine*)(addr[0x6a]);
		TextboxLine *linePointerStart	=	(TextboxLine*)(addr[0x6a]);
		TextboxLine *linePointerEnd		=	(TextboxLine*)(addr[0x6b]);
		wchar_t wsz[256];
		int len = strlen(text);

		swprintf( wsz, L"%S", text );
		
		int numElements = linePointerEnd-linePointer;

		for(;linePointer < linePointerEnd; linePointer++)
		{
			if(!linePointer->text)
				continue;
			
			if(wcsncmp(wsz, linePointer->text, len) == 0)
				return linePointer-linePointerStart;
		}

		return -1;
	}

	FEX int FindLine( int start, const char* text ) const
	{
		DWORD *addr = (DWORD *) this;
		TextboxLine *linePointer		=	(TextboxLine*)(addr[0x6a]);
		TextboxLine *linePointerStart	=	(TextboxLine*)(addr[0x6a]);
		TextboxLine *linePointerEnd		=	(TextboxLine*)(addr[0x6b]);
		wchar_t wsz[256];
		int len = strlen(text);

		swprintf( wsz, L"%S", text );
		
		int numElements = linePointerEnd-linePointer;

		linePointer += start;

		for(;linePointer < linePointerEnd; linePointer++)
		{
			if(!linePointer->text)
				continue;
			
			if(wcsncmp(wsz, linePointer->text, len) == 0)
				return linePointer-linePointerStart;
		}

		return -1;
	}

	FEX int FindLine( const wchar_t* text ) const
	{
		DWORD *addr = (DWORD *) this;
		TextboxLine *linePointer		=	(TextboxLine*)(addr[0x6a]);
		TextboxLine *linePointerStart	=	(TextboxLine*)(addr[0x6a]);
		TextboxLine *linePointerEnd		=	(TextboxLine*)(addr[0x6b]);
		int len = wcslen(text);
		
		int numElements = linePointerEnd-linePointer;

		for(;linePointer < linePointerEnd; linePointer++)
		{
			if(!linePointer->text)
				continue;

			if(wcsncmp(text, linePointer->text, len) == 0)
				return linePointer-linePointerStart;
		}

		return -1;
	}
	
#if 0
	FEX void CorrectDamageLine( int amount )
	{
		DWORD *addr = (DWORD *) this;
		TextboxLine *linePointer = 	(TextboxLine*)(addr[0x6a]);
		int line = FindLine( L"Damage:" );

		if( line >= 0 )
		{
			int value;

			linePointer += line;

			ComplexLine *complexPointer = linePointer->startComplex + 1;

			value = _wtoi(complexPointer->text);
			value -= amount;
			_itow(value, (wchar_t*)complexPointer->text, 10);

			complexPointer += 2;

			value = _wtoi(complexPointer->text);
			value -= amount;
			_itow(value, (wchar_t*)complexPointer->text, 10);

			ComplexLine *complexPointer1 = linePointer->startComplex;
			ComplexLine *complexPointer2 = linePointer->startComplex + 1;
			ComplexLine *complexPointer3 = linePointer->startComplex + 2;
			ComplexLine *complexPointer4 = linePointer->startComplex + 3;

			/*swprintf((wchar_t*)linePointer->text, L"%s %s %s %s",
				complexPointer1->text,
				complexPointer2->text,
				complexPointer3->text,
				complexPointer4->text);*/
		}
	}
#endif
};

enum UI_CONTROL_TYPE
{
	UI_TYPE_WINDOW = 0,
	UI_TYPE_BUTTON,
	UI_TYPE_CHECKBOX,
	UI_TYPE_SLIDER,
	UI_TYPE_LISTBOX,
	UI_TYPE_RADIO_BUTTON,
	UI_TYPE_BUTTON_MULTISTAGE,
	UI_TYPE_TEXT,
	UI_TYPE_CURSOR,
	UI_TYPE_DOCKBAR,
	UI_TYPE_GRIDBOX,
	UI_TYPE_POPUPMENU,
	UI_TYPE_ITEM,
	UI_TYPE_ITEMSLOT,
	UI_TYPE_INFOSLOT,
	UI_TYPE_STATUS_BAR,
	UI_TYPE_EDIT_BOX,
	UI_TYPE_COMBO_BOX,
	UI_TYPE_LISTENER,
	UI_TYPE_LISTREPORT,
	UI_TYPE_CHAT_BOX,
	UI_TYPE_TEXT_BOX,
	UI_TYPE_DIALOG_BOX,
	UI_TYPE_TAB,
};

class UIWindow
{
public:
	UI_CONTROL_TYPE GetType() const
	{
		UI_CONTROL_TYPE *addr = (UI_CONTROL_TYPE *) this;
		return addr[0x01];
	}
};

struct TextLine
{
	wchar_t *text;
	DWORD unknown1;
	DWORD unknown2;
	DWORD unknown3;
};

struct UnknownStruct1
{
	DWORD unknown1;
	DWORD unknown2;
	wchar_t *text;
	DWORD unknown3;
};

struct ConsoleLine
{
	DWORD unknown1;
	TextLine* textLine;
	UnknownStruct1* unknown_p1;
	UnknownStruct1* unknown_p2;
	DWORD unknown2;
};

class UIChatBox
{
	FUBI_CLASS_INHERIT( UIChatBox, UIWindow );

	FEX const char* GetNewestLine( ) const
	{
		DWORD *addr = (DWORD *) this;
		ConsoleLine *linePointer = 	(ConsoleLine*)(addr[0x6f]);

		if(addr[0x6e] == addr[0x6f])
		{
			buffer[0] = '\0';
			return buffer;
		}
				
		linePointer--;

		TextLine *textLine = linePointer->textLine;

		if(textLine && textLine->text)
		{
			sprintf(buffer, "%S", textLine->text);
		}
		else
		{
			buffer[0] = '\0';
		}

		return buffer;
	}

	FEX void SetNewestLine( const char *text )
	{
		DWORD *addr = (DWORD *) this;
		ConsoleLine *linePointer = 	(ConsoleLine*)(addr[0x6f]);

		if(addr[0x6e] == addr[0x6f])
			return;
				
		linePointer--;

		TextLine *textLine = linePointer->textLine;

		if(textLine && textLine->text)
		{
			_snwprintf( textLine->text, wcslen(textLine->text), L"%S", text );
		}
	}

	FEX bool NewestLineContains( const char *text ) const
	{
		DWORD *addr = (DWORD *) this;
		ConsoleLine *linePointer = 	(ConsoleLine*)(addr[0x6f]);

		if(addr[0x6e] == addr[0x6f])
			return false;
				
		linePointer--;

		TextLine *textLine = linePointer->textLine;

		if(textLine && textLine->text)
		{
			sprintf(buffer, "%S", textLine->text);
		}
		else
		{
			buffer[0] = '\0';
		}

		return (strstr(buffer, text) != NULL);
	}

	FEX void ClearConsole()
	{
		DWORD *addr = (DWORD *) this;
		addr[0x6e] = addr[0x6f];
	}
};

FEX UIChatBox* QueryDerivedChatBox( UIWindow* base )
{
   if ( (base != NULL) && (base->GetType() == UI_TYPE_CHAT_BOX) )
   {
      return ( (UIChatBox*)base );
   }
   return ( NULL );
}

struct Goid_;

class Go
{
	int unknown1;
};

class UIShell
{
	FEX DWORD GetRolloverID( ) const
	{
		DWORD *addr = (DWORD *) this;
		return addr[0x2b];
	}
	
	FEX const Goid_ *GetRolloverGoID( ) const
	{
		DWORD *addr = (DWORD *) this;
		return (Goid_*)addr[0x2b];
	}

	// probably not "Window", but something like that
	FEX const char* GetRolloverKey( ) const
	{
		DWORD *addr = (DWORD *) this;
		return (const char*)addr[0x39];
	}

	FEX bool IsItemDragged( ) const
	{
		DWORD *addr = (DWORD *) this;
		return (bool)(!!addr[0x0d]);
	}
};

class GoInventory
{
	FEX const Go *GetOpenSpellbook( ) const
	{
		DWORD *addr = (DWORD *) this;

		Go *pSpellBook = (Go *)addr[OFFSET_OPEN_SPELLBOOK];

		return pSpellBook;
	}
};

#ifndef LOA
class WorldMap
{
	FEX const char* GetMapName( ) const
	{		
		DWORD *addr = (DWORD *) this;
		return (const char*)(addr[0x01]);
	}
};
#endif

class GoAttack
{
	FEX float GetBaseDamageMin( ) const
	{
		float *addr = (float *) this;

		return addr[0x09];
	}

	FEX float GetBaseDamageMax( ) const
	{		
		float *addr = (float *) this;

		return addr[0x0b];
	}

	FEX void SetBaseDamageMin( float value )
	{		
		float *addr = (float *) this;

		addr[0x09] = value;
	}

	FEX void SetBaseDamageMax( float value )
	{		
		float *addr = (float *) this;

		addr[0x0b] = value;
	}
};

class Globals : public Singleton <Globals>
{
public:
	#define gGlobals Globals::GetSingleton()

private:
	
	FUBI_VARIABLE( eInventoryLocation, m_, Hover, "Currently hovered over spell icon slot" );
	FUBI_VARIABLE( int, m_, Character, "Currently hovered over character" );
	FUBI_SINGLETON_CLASS( Globals, "New global variables for UI (Author: Jason 'Ikkyo' Gripp)." );
};
Globals g_Globals;

const char *character_max[] = 
{
	"character_1_max",
	"character_2_max",
	"character_3_max",
	"character_4_max",
	"character_5_max",
	"character_6_max",
	"character_7_max",
	"character_8_max"
};

const char *swaptoggle_on[] = 
{
	"swaptoggle_on_1",
	"swaptoggle_on_2",
	"swaptoggle_on_3",
	"swaptoggle_on_4",
	"swaptoggle_on_5",
	"swaptoggle_on_6",
	"swaptoggle_on_7",
	"swaptoggle_on_8"
};

const char *swaptoggle_off[] = 
{
	"swaptoggle_off_1",
	"swaptoggle_off_2",
	"swaptoggle_off_3",
	"swaptoggle_off_4",
	"swaptoggle_off_5",
	"swaptoggle_off_6",
	"swaptoggle_off_7",
	"swaptoggle_off_8"
};

const char *icon_backdrop[] = 
{
	"icon_backdrop_1",
	"icon_backdrop_2",
	"icon_backdrop_3",
	"icon_backdrop_4",
	"icon_backdrop_5",
	"icon_backdrop_6",
	"icon_backdrop_7",
	"icon_backdrop_8",
};

const char *spell_icon[] = 
{
	"spell_icon_character_1_slot_2",
	"spell_icon_character_1_slot_3",
	"spell_icon_character_1_slot_4",
	"spell_icon_character_1_slot_5",
	"spell_icon_character_1_slot_6",
	"spell_icon_character_1_slot_7",
	"spell_icon_character_1_slot_8",
	"spell_icon_character_1_slot_9",
	"spell_icon_character_1_slot_10",
	"spell_icon_character_1_slot_11",
	"spell_icon_character_1_slot_12",

	"spell_icon_character_2_slot_2",
	"spell_icon_character_2_slot_3",
	"spell_icon_character_2_slot_4",
	"spell_icon_character_2_slot_5",
	"spell_icon_character_2_slot_6",
	"spell_icon_character_2_slot_7",
	"spell_icon_character_2_slot_8",
	"spell_icon_character_2_slot_9",
	"spell_icon_character_2_slot_10",
	"spell_icon_character_2_slot_11",
	"spell_icon_character_2_slot_12",

	"spell_icon_character_3_slot_2",
	"spell_icon_character_3_slot_3",
	"spell_icon_character_3_slot_4",
	"spell_icon_character_3_slot_5",
	"spell_icon_character_3_slot_6",
	"spell_icon_character_3_slot_7",
	"spell_icon_character_3_slot_8",
	"spell_icon_character_3_slot_9",
	"spell_icon_character_3_slot_10",
	"spell_icon_character_3_slot_11",
	"spell_icon_character_3_slot_12",

	"spell_icon_character_4_slot_2",
	"spell_icon_character_4_slot_3",
	"spell_icon_character_4_slot_4",
	"spell_icon_character_4_slot_5",
	"spell_icon_character_4_slot_6",
	"spell_icon_character_4_slot_7",
	"spell_icon_character_4_slot_8",
	"spell_icon_character_4_slot_9",
	"spell_icon_character_4_slot_10",
	"spell_icon_character_4_slot_11",
	"spell_icon_character_4_slot_12",

	"spell_icon_character_5_slot_2",
	"spell_icon_character_5_slot_3",
	"spell_icon_character_5_slot_4",
	"spell_icon_character_5_slot_5",
	"spell_icon_character_5_slot_6",
	"spell_icon_character_5_slot_7",
	"spell_icon_character_5_slot_8",
	"spell_icon_character_5_slot_9",
	"spell_icon_character_5_slot_10",
	"spell_icon_character_5_slot_11",
	"spell_icon_character_5_slot_12",

	"spell_icon_character_6_slot_2",
	"spell_icon_character_6_slot_3",
	"spell_icon_character_6_slot_4",
	"spell_icon_character_6_slot_5",
	"spell_icon_character_6_slot_6",
	"spell_icon_character_6_slot_7",
	"spell_icon_character_6_slot_8",
	"spell_icon_character_6_slot_9",
	"spell_icon_character_6_slot_10",
	"spell_icon_character_6_slot_11",
	"spell_icon_character_6_slot_12",

	"spell_icon_character_7_slot_2",
	"spell_icon_character_7_slot_3",
	"spell_icon_character_7_slot_4",
	"spell_icon_character_7_slot_5",
	"spell_icon_character_7_slot_6",
	"spell_icon_character_7_slot_7",
	"spell_icon_character_7_slot_8",
	"spell_icon_character_7_slot_9",
	"spell_icon_character_7_slot_10",
	"spell_icon_character_7_slot_11",
	"spell_icon_character_7_slot_12",

	"spell_icon_character_8_slot_2",
	"spell_icon_character_8_slot_3",
	"spell_icon_character_8_slot_4",
	"spell_icon_character_8_slot_5",
	"spell_icon_character_8_slot_6",
	"spell_icon_character_8_slot_7",
	"spell_icon_character_8_slot_8",
	"spell_icon_character_8_slot_9",
	"spell_icon_character_8_slot_10",
	"spell_icon_character_8_slot_11",
	"spell_icon_character_8_slot_12"
};

const char *swap_control[] = 
{
	"swap_control_character_1_slot_2",
	"swap_control_character_1_slot_3",
	"swap_control_character_1_slot_4",
	"swap_control_character_1_slot_5",
	"swap_control_character_1_slot_6",
	"swap_control_character_1_slot_7",
	"swap_control_character_1_slot_8",
	"swap_control_character_1_slot_9",
	"swap_control_character_1_slot_10",
	"swap_control_character_1_slot_11",
	"swap_control_character_1_slot_12",

	"swap_control_character_2_slot_2",
	"swap_control_character_2_slot_3",
	"swap_control_character_2_slot_4",
	"swap_control_character_2_slot_5",
	"swap_control_character_2_slot_6",
	"swap_control_character_2_slot_7",
	"swap_control_character_2_slot_8",
	"swap_control_character_2_slot_9",
	"swap_control_character_2_slot_10",
	"swap_control_character_2_slot_11",
	"swap_control_character_2_slot_12",

	"swap_control_character_3_slot_2",
	"swap_control_character_3_slot_3",
	"swap_control_character_3_slot_4",
	"swap_control_character_3_slot_5",
	"swap_control_character_3_slot_6",
	"swap_control_character_3_slot_7",
	"swap_control_character_3_slot_8",
	"swap_control_character_3_slot_9",
	"swap_control_character_3_slot_10",
	"swap_control_character_3_slot_11",
	"swap_control_character_3_slot_12",

	"swap_control_character_4_slot_2",
	"swap_control_character_4_slot_3",
	"swap_control_character_4_slot_4",
	"swap_control_character_4_slot_5",
	"swap_control_character_4_slot_6",
	"swap_control_character_4_slot_7",
	"swap_control_character_4_slot_8",
	"swap_control_character_4_slot_9",
	"swap_control_character_4_slot_10",
	"swap_control_character_4_slot_11",
	"swap_control_character_4_slot_12",

	"swap_control_character_5_slot_2",
	"swap_control_character_5_slot_3",
	"swap_control_character_5_slot_4",
	"swap_control_character_5_slot_5",
	"swap_control_character_5_slot_6",
	"swap_control_character_5_slot_7",
	"swap_control_character_5_slot_8",
	"swap_control_character_5_slot_9",
	"swap_control_character_5_slot_10",
	"swap_control_character_5_slot_11",
	"swap_control_character_5_slot_12",

	"swap_control_character_6_slot_2",
	"swap_control_character_6_slot_3",
	"swap_control_character_6_slot_4",
	"swap_control_character_6_slot_5",
	"swap_control_character_6_slot_6",
	"swap_control_character_6_slot_7",
	"swap_control_character_6_slot_8",
	"swap_control_character_6_slot_9",
	"swap_control_character_6_slot_10",
	"swap_control_character_6_slot_11",
	"swap_control_character_6_slot_12",

	"swap_control_character_7_slot_2",
	"swap_control_character_7_slot_3",
	"swap_control_character_7_slot_4",
	"swap_control_character_7_slot_5",
	"swap_control_character_7_slot_6",
	"swap_control_character_7_slot_7",
	"swap_control_character_7_slot_8",
	"swap_control_character_7_slot_9",
	"swap_control_character_7_slot_10",
	"swap_control_character_7_slot_11",
	"swap_control_character_7_slot_12",

	"swap_control_character_8_slot_2",
	"swap_control_character_8_slot_3",
	"swap_control_character_8_slot_4",
	"swap_control_character_8_slot_5",
	"swap_control_character_8_slot_6",
	"swap_control_character_8_slot_7",
	"swap_control_character_8_slot_8",
	"swap_control_character_8_slot_9",
	"swap_control_character_8_slot_10",
	"swap_control_character_8_slot_11",
	"swap_control_character_8_slot_12",
};

class UIHelper : public Singleton <UIHelper>
{
public:
	#define gUIHelper UIHelper::GetSingleton()

	FEX static const char *GetCharacterGroupMax( int c )
	{
		return character_max[c - 1];
	}

	FEX static const char *GetSwapToggleOn( int c )
	{
		return swaptoggle_on[c - 1];
	}

	FEX static const char *GetSwapToggleOff( int c )
	{
		return swaptoggle_off[c - 1];
	}

	FEX static const char *GetIconBackdrop( int c )
	{
		return icon_backdrop[c - 1];
	}

	FEX static const char *GetSpellIcon( int character, int slot )
	{
		return spell_icon[(character - 1) * 11 + (slot - 2)];
	}

	FEX static const char *GetSwapControl( int character, int slot )
	{
		return swap_control[(character - 1) * 11 + (slot - 2)];
	}

private:
	
	FUBI_SINGLETON_CLASS( UIHelper, "Stores some helper functions for UI (Author: Jason 'Ikkyo' Gripp)." );
};
UIHelper g_UIHelper;

FEX bool IsKeyPressed( DWORD key )
{
	return !!(GetAsyncKeyState(key) & 0x8000);
}

FEX const char *dsdllVersion()
{
	return "v1.5.5";
}

struct SkillEntry
{
	const char *name;
	DWORD unknown1;
	const char *screen_name;
	DWORD unknown2;
	float str_influence;
	float dex_influence;
	float int_influence;
	DWORD unknown3;
	DWORD unknown4;
	float value1;
	DWORD unknown5;
	float value2;
	float base_level;
	float current_level;
	DWORD unknown6;
	DWORD unknown7;
	float max_level;
	void *owner;
};

class GoActor
{
	FEX void SetBaseSkillLevel( const char* skill, float value )
	{
		DWORD *addr = (DWORD *) this;

		SkillEntry *skillEnd	= (SkillEntry*)(addr[0x07]);

		for(SkillEntry *skillEntry = (SkillEntry*)(addr[0x06]); skillEntry < skillEnd; skillEntry++)
		{
			if(stricmp(skill, skillEntry->name) == 0)
			{
				skillEntry->base_level = value;
				return;
			}
		}
	}
	
	FEX void ChangeBaseSkillLevel( const char* skill, float delta )
	{
		DWORD *addr = (DWORD *) this;
		SkillEntry *skillEnd	= (SkillEntry*)(addr[0x07]);

		for(SkillEntry *skillEntry = (SkillEntry*)(addr[0x06]); skillEntry < skillEnd; skillEntry++)
		{
			if(stricmp(skill, skillEntry->name) == 0)
			{
				skillEntry->base_level += delta;

				if(skillEntry->base_level < 0)
				{
					skillEntry->base_level = 0;
					return;
				}
			}
		}
	}

	FEX float GetBaseSkillLevel( const char* skill ) const
	{
		DWORD *addr = (DWORD *) this;

		SkillEntry *skillEnd	= (SkillEntry*)(addr[0x07]);

		for(SkillEntry *skillEntry = (SkillEntry*)(addr[0x06]); skillEntry < skillEnd; skillEntry++)
		{
			if(stricmp(skill, skillEntry->name) == 0)
			{
				return skillEntry->base_level;
			}
		}

		return 0.0f;
	}
};

class GoAspect
{
	FEX void SetRenderScale( float value )
	{
		float *addr = (float *) this;

		addr[0x06] = value;
	}

#ifndef LOA
	FEX const char *GetDynamicTexture( ePlayerSkin skin ) const
	{
		gp_string **addr = (gp_string **) this;

		if (skin == PS_FLESH)
			return addr[0x0a]->c_str();
		else if (skin == PS_CLOTH)
			return addr[0x0b]->c_str();
		else
			return "";
	}
#endif

	FEX const char *GetDynamicTexture( int skin ) const
	{
		gp_string **addr = (gp_string **) this;

		if (skin == PS_FLESH)
			return addr[0x0a]->c_str();
		else if (skin == PS_CLOTH)
			return addr[0x0b]->c_str();
		else
			return "";
	}
};

struct GridItem
{
	DWORD unknown1;	// 85 01 00 00
	DWORD unknown2;	// 1E 00 00 00
	DWORD unknown3;	// A5 01 00 00
	DWORD unknown4;	// 3E 00 00 00
	DWORD unknown5;	// 00 00 80 3F
	DWORD unknown6;	// 00 00 80 3F
	Goid_ *goid;	// CF 00 05 12
	DWORD unknown7;	// 01 00 00 00
	DWORD unknown8;	// E4 F7 12 00
	DWORD unknown9;	// 00 3C 04 0B
};

struct GridCell
{
	DWORD unknown1;	// 85 01 00 00
	DWORD unknown2;	// 1E 00 00 00
	DWORD unknown3;	// A5 01 00 00
	DWORD unknown4;	// 3E 00 00 00
	bool filled;	// 01 CD CD CD
	Goid_ *item_goid;	// CF 00 08 12
};

enum eFormulaInputType
{
	FIT_NONE = 0,
	FIT_TEMPLATE,
};

struct FormulaInput
{
	eFormulaInputType type;
	const char *template_name;
	int parameter;
};

struct ItemInfo
{
	const char *template_name;
	bool used;
};

#define MAX_ITEMS 20

ItemInfo g_ItemInfo[MAX_ITEMS];
int g_numItems = 0;

struct FormulaEntry
{
	int num_inputs;
	int num_slots;

	FormulaInput input[7];

	const char* output;
};

FormulaEntry g_FormulaTable[] = {
	{ 3, 1, { {FIT_TEMPLATE, "potion_health_small",	 3}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE} },	"potion_health_medium"	},
	{ 3, 1, { {FIT_TEMPLATE, "potion_health_medium", 3}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE} },	"potion_health_large"	},
	{ 3, 1, { {FIT_TEMPLATE, "potion_health_large",	 3}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE} },	"potion_health_super"	},

	{ 3, 1, { {FIT_TEMPLATE, "potion_mana_small",	 3}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE} },	"potion_mana_medium"	},
	{ 3, 1, { {FIT_TEMPLATE, "potion_mana_medium", 3}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE} },	"potion_mana_large"		},
	{ 3, 1, { {FIT_TEMPLATE, "potion_mana_large",	 3}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE} },	"potion_mana_super"		},

	{ 3, 1, { {FIT_TEMPLATE, "ring_common",	 3}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE} },	"#amulet/0-100"	},
	{ 3, 1, { {FIT_TEMPLATE, "amulet_common", 3}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE} },	"#ring/0-100"	},

	{ 0, 0, { {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE}, {FIT_NONE} }, ""},
};

static int FindItem( const char* template_name )
{
	for(int i = 0; i < MAX_ITEMS; i++)
	{
		if(!g_ItemInfo[i].used)
		{
			if(strcmp(template_name, g_ItemInfo[i].template_name) == 0)
				return i;
		}
	}
	
	return -1;
}

class UIGridbox
{
	FEX int GetNumItems() const
	{
		DWORD *addr = (DWORD *) this;
		return ((GridItem*)addr[0xeafd]-(GridItem*)addr[0xeafc]);
	}

	FEX const Goid_* GetItemGoid(int index) const
	{
		DWORD *addr = (DWORD *) this;

		GridItem *startItem	= (GridItem*)addr[0xeafc];
		GridItem *endItem	= (GridItem*)addr[0xeafd];

		int num_items = endItem-startItem;

		if(index < 0 || index >= num_items)
		{
			return (Goid_*)0xffffffff;
		}
		else
		{
			startItem += index;

			return startItem->goid;
		}
	}

	FEX bool IsCellFilled(int x, int y) const
	{
		DWORD addr = (DWORD) this;

		GridCell *cell = (GridCell*)(addr + 0x264);

		cell += (y*100 + x);

		DWORD *paddr = (DWORD *) this;

		GridItem *startItem	= (GridItem*)paddr[0xeafc];

		return cell->filled;
	}

	FEX void ClearGridBox(int wide, int tall)
	{
		DWORD addr = (DWORD) this;

		GridCell *cell = (GridCell*)(addr + 0x264);

		for(int y = 0; y < tall; y++)
		{
			for(int x = 0; x < wide; x++)
			{
				cell->filled = false;
				cell->item_goid = (Goid_*)0xffffffff;
				cell++;
			}

			cell += (100-wide);
		}

		DWORD *paddr = (DWORD *) this;
		paddr[0xeafd] = paddr[0xeafc];
	}

	FEX void BeginTransmute()
	{
		// Reset the array
		for(int index = 0; index < MAX_ITEMS; index++)
		{
			g_ItemInfo[index].template_name = "";
			g_ItemInfo[index].used = false;
		}

		g_numItems = 0;
	}

	// For supplying some needed information to the dsdll
	// Only the template name at this point, but it will eventually
	// include whether the item is magical, a weapon, etc.
	FEX void AddItemInfo(const char* template_name)
	{
		// Add an entry to the array
		g_ItemInfo[g_numItems].template_name = template_name;
		
		g_numItems++;
	}

	FEX const char* Transmute()
	{
		// Look for a matching transmute formula
		int index = 0;

		while(g_FormulaTable[index].num_inputs > 0)
		{
			if(g_FormulaTable[index].num_inputs > g_numItems) {
				index++;
				continue;
			}

			for(int i = 0; i < MAX_ITEMS; i++)
			{
				g_ItemInfo[i].used = false;
			}

			bool error = false;

			for(int inputx = 0; inputx < g_FormulaTable[index].num_inputs && !error; inputx++)
			{
				int item = -1;
				int q;

				switch(g_FormulaTable[index].input[inputx].type)
				{
				case FIT_TEMPLATE:
					for( q = 0; q < g_FormulaTable[index].input[inputx].parameter && !error; q++ )
					{
						item = FindItem(g_FormulaTable[index].input[inputx].template_name);

						if(item == -1) {
							error = true;
						} else {
							g_ItemInfo[item].used = true;
						}
					}

					break;
				default:
					break;
				}
			}

			// See if all inputs were valid
			if(inputx == g_FormulaTable[index].num_inputs)
			{
				return g_FormulaTable[index].output;
			}

			index++;
		}

		return "";
	}
};

class SiegeCamera
{
	FEX void SetMaxAzimuth( float value )
	{
		float *addr = (float *) this;
		addr[0x6b] = value;
	}

	FEX void SetMinAzimuth( float value )
	{
		float *addr = (float *) this;
		addr[0x6c] = value;
	}

	FEX void SetMaxDistance( float value )
	{
		float *addr = (float *) this;
		addr[0x6d] = value;
	}

	FEX void SetMinDistance( float value )
	{
		float *addr = (float *) this;
		addr[0x6e] = value;
	}
};

class UISlider
{
	FUBI_CLASS_INHERIT( UISlider, UIWindow );

	FEX int GetValue( )
	{
		int *addr = (int *) this;

		return addr[0x7a];
	}

	FEX void SetValue( int value )
	{
		int *addr = (int *) this;

		addr[0x7a] = value;
	}
};

FEX UISlider* QueryDerivedSlider( UIWindow* base )
{
   if ( (base != NULL) && (base->GetType() == UI_TYPE_SLIDER) )
   {
      return ( (UISlider*)base );
   }
   return ( NULL );
}

class Math
{
	FEX static float Arccos( float x )
	{
		return (float)acos(x);
	}

	FEX static float Arcsin( float x )
	{
		return (float)asin(x);
	}

	FEX static float Arctan( float x )
	{
		return (float)atan(x);
	}

	FEX static float Arctan2( float y, float x )
	{
		return (float)atan2(y,x);
	}

	FEX static float Cosh( float x )
	{
		return (float)cosh(x);
	}

	FEX static float Exp( float x )
	{
		return (float)exp(x);
	}

	FEX static bool Finite( float x )
	{
		return !!_finite(x);
	}

	FEX static float FMod( float x, float y )
	{
		return (float)fmod(x,y);
	}

	FEX static float Hypotenuse( float x, float y )
	{
		return (float)hypot(x,y);
	}

	FEX static float Ln( float x )
	{
		return (float)log(x);
	}

	FEX static float Log( float x )
	{
		return (float)log10(x);
	}

	FEX static int ShiftL( int x, int y )
	{
		return x << y;
	}

	FEX static int ShiftR( int x, int y )
	{
		return x >> y;
	}

	FEX static float Power( float x, float y )
	{
		return (float)pow(x,y);
	}

	FEX static float Sinh( float x )
	{
		return (float)sinh(x);
	}

	FEX static float Sqrt( float x )
	{
		return (float)sqrt(x);
	}

	FEX static float Tanh( float x )
	{
		return (float)tanh(x);
	}

	FEX static float ToFloat( const char *a )
	{
		return (float)atof(a);
	}

	FEX static int ToInt( const char *a )
	{
		return atoi(a);
	}
};

///////////////////////////////////////////////////////////////////////////////