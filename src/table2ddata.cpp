/***************************************************************************
*   Copyright (C) 2012  Michael Carpenter (malcom2073)                     *
*                                                                          *
*   This file is a part of EMStudio                                        *
*                                                                          *
*   EMStudio is free software: you can redistribute it and/or modify       *
*   it under the terms of the GNU General Public License version 2 as      *
*   published by the Free Software Foundation.                             *
*                                                                          *
*   EMStudio is distributed in the hope that it will be useful,            *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
*   GNU General Public License for more details.                           *
									   *
*   You should have received a copy of the GNU General Public License      *
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.  *
****************************************************************************/

#include "table2ddata.h"

Table2DData::Table2DData()
{

}

Table2DData::Table2DData(unsigned short locationid,QByteArray payload)
{
	setData(locationid,payload);
}

void Table2DData::setData(unsigned short locationid, QByteArray payload)
{
	m_locationId = locationid;
	for (int i=0;i<payload.size()/2;i+=2)
	{
		unsigned short x = (((unsigned char)payload[i]) << 8) + ((unsigned char)payload[i+1]);
		unsigned short y = (((unsigned char)payload[(payload.size()/2)+ i]) << 8) + ((unsigned char)payload[(payload.size()/2) + i+1]);
		m_xaxis.append(x);
		m_yaxis.append(y);
	}
}

QByteArray Table2DData::data()
{
	QByteArray data;
	for (int i=0;i<m_xaxis.size();i++)
	{
		data.append((char)((m_xaxis[i] >> 8) & 0xFF));
		data.append((char)(m_xaxis[i] & 0xFF));
	}
	for (int i=0;i<m_yaxis.size();i++)
	{
		data.append((char)((m_yaxis[i] >> 8) & 0xFF));
		data.append((char)(m_yaxis[i] & 0xFF));
	}
	return data;
}