/**********************************************************************
 * $Id$
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 ***********************************************************************
 *
 * Last port: precision/LineStringSnapper.java rev. 0
 *
 **********************************************************************/

#ifndef GEOS_PRECISION_LINESTRINGSNAPPER_H
#define GEOS_PRECISION_LINESTRINGSNAPPER_H

#include <geos/geom/Coordinate.h>
#include <geos/geom/CoordinateSequence.h>
#include <geos/geom/CoordinateList.h>

#include <memory>

// Forward declarations
namespace geos {
	namespace geom { 
		//class PrecisionModel;
		//class CoordinateSequence;
		class CoordinateList;
		class Geometry;
	}
}

namespace geos {
namespace precision { // geos.precision

/** \brief
 * Snaps the vertices and segments of a LineString to another's vertices.
 * Should improve robustness for overlay operations.
 *
 */
class LineStringSnapper {

public:

	LineStringSnapper(const geom::Coordinate::Vect& nSrcPts, double nSnapTol)
		:
		srcPts(nSrcPts),
		snapTolerance(nSnapTol)
	{
		size_t s = srcPts.size();
		isClosed = ( s < 2 || srcPts[0].equals2D(srcPts[s-1]) );
	}

	// Snap points are assumed to be all distinct points (a set would be better, uh ?)
	std::auto_ptr<geom::Coordinate::Vect> snapTo(const geom::Coordinate::ConstVect& snapPts);

private:

	const geom::Coordinate::Vect& srcPts;

	double snapTolerance;

	bool isClosed;


	// Modifies first arg
	void snapVertices(geom::CoordinateList& srcCoords,
			const geom::Coordinate::ConstVect& snapPts);


	// Returns snapPts.end() if no snap point is close enough (within snapTol distance)
	geom::Coordinate::ConstVect::const_iterator findSnapForVertex(const geom::Coordinate& pt,
			const geom::Coordinate::ConstVect& snapPts);

	// Modifies first arg
	void snapSegments(geom::CoordinateList& srcCoords,
			const geom::Coordinate::ConstVect& snapPts);

	/// \brief
	/// Returns an iterator to the first point of the first segment in
	/// srcPts which is within snapTolerance distance from given snapPt.
	/// 
	/// @param from
	///        an iterator to first point of first segment to be checked
	///
	/// @param too_far
	///        an iterator to last point of last segment to be checked
	///
	/// @returns too_far if no segment is close enough
	///          (within snapTol distance)
	///
	geom::CoordinateList::iterator findSegmentToSnap(
			const geom::Coordinate& snapPt,
			geom::CoordinateList::iterator from,
			geom::CoordinateList::iterator too_far);

};


} // namespace geos.precision
} // namespace geos

#endif // GEOS_PRECISION_LINESTRINGSNAPPER_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/07/21 17:09:14  strk
 * Added new precision::LineStringSnapper class + test
 * and precision::GeometrySnapper (w/out test)
 *
 **********************************************************************/
