/*
 * Licensed under the 'LICENSE'.
 * See LICENSE file in the project root for full license information.
 */
#ifndef LINEARCONVERTER_H
#define LINEARCONVERTER_H

#include "Range.h"

#include <stdio.h>
namespace LibBBB {
namespace Math {

/**
 * @brief	The LinearConverter class converts x to y or y to x using slope intercept formula.
 *			Basically, this class wraps mx + b, and allows conversion in the other direction.
 */
template< typename DataType >
class LinearConverter
{
public:

	// typedef of the range for convenience
	typedef Range< DataType > RangeType;

private:

	// x and y ranges
	const RangeType _xRange;
	const RangeType _yRange;

	// slope and y intercept
	DataType _denominatorSlope;
	DataType _numeratorSlope;
	DataType _b;

public:

	/**
	 * @brief LinearConverter constructor
	 * @param xValue range of the x value
	 * @param yValue range of the y value
	 */
	LinearConverter( const RangeType& xValue, const RangeType& yValue )
		: _xRange( xValue)
		, _yRange( yValue )
		, _denominatorSlope( xValue.range() )
		, _numeratorSlope( yValue.range() )
		, _b( -xValue.lowValue() * _numeratorSlope / _denominatorSlope + yValue.lowValue() )
	{}

	/**
	 * @brief convertXtoY getter. Uses y = mx + b.
	 * @param x value
	 * @return mx + b
	 */
	inline DataType convertXtoY( const DataType& x ) const
	{
		DataType returnValue = x * _numeratorSlope / _denominatorSlope + _b;
		return boundValue( returnValue, _yRange.lowValue(), _yRange.highValue() );
	}

	/**
	 * @brief convertYtoX getter. Uses x = ( y - b ) / m.
	 * @param y value
	 * @return ( y - b ) / m
	 */
	inline DataType convertYtoX( const DataType& y ) const
	{
		DataType returnValue = ( y - _b ) * _denominatorSlope / _numeratorSlope;
		return boundValue( returnValue, _xRange.lowValue(), _xRange.highValue() );
	}

private:

	/**
	 * @brief	boundValue method returns the bounded value based on the
	 *			given high and low values
	 * @param value to be bounded
	 * @param low lowest value "value" can be
	 * @param high highest value "value" can be
	 * @return bounded value
	 */
	inline DataType boundValue( const DataType& value, const DataType& low, const DataType& high ) const
	{
		if ( value < low )
		{
			return low;
		}

		if ( value > high )
		{
			return high;
		}

		return value;
	}
};

/**
 * @brief	The LinearConverter class converts x to y or y to x using slope intercept formula.
 *			Basically, this class wraps mx + b, and allows conversion in the other direction.
 */
template<>
class LinearConverter< float >
{

public:

	typedef Range< float > RangeType;


private:

	float _slope;
	float _b;


public:

	/**
	 * Constructs a new instance of LinearConverter.
	 * @param xRange
	 * @param yRange
	 **/
	LinearConverter( const RangeType& xValue, const RangeType& yValue )
		: _slope( yValue.range() / xValue.range() )
		, _b( -xValue.lowValue() * _slope + yValue.lowValue() )
	{
	}

	/**
	 * Gets the Y value associated with the given X value.
	 * @param x
	 **/
	inline float convertXtoY( const float& x ) const
	{
		return x * _slope + _b;
	}

	/**
	 * Gets the X value associated with the given Y value.
	 * @param y
	 **/
	inline float convertYtoX( const float& y ) const
	{
		return ( y - _b ) / _slope;
	}
};

/**
 * @brief	The LinearConverter class converts x to y or y to x using slope intercept formula.
 *			Basically, this class wraps mx + b, and allows conversion in the other direction.
 */
template<>
class LinearConverter< double >
{

public:

	typedef Range< double > RangeType;


private:
	// x and y ranges
	const RangeType _xRange;
	const RangeType _yRange;

	double _slope;
	double _b;

public:

	/**
	 * Constructs a new instance of LinearConverter.
	 * @param xRange
	 * @param yRange
	 **/
	LinearConverter( const RangeType& xValue, const RangeType& yValue )
		: _xRange( xValue)
		, _yRange( yValue )
		, _slope( yValue.range() / xValue.range() )
		, _b( -xValue.lowValue() * _slope + yValue.lowValue() )
	{
	}

	/**
	 * Gets the Y value associated with the given X value.
	 * @param x
	 **/
	inline double convertXtoY( const double& x ) const
	{
		double result = x * _slope + _b;
		return boundValue( result, _xRange.lowValue(), _xRange.highValue() );
	}

	/**
	 * Gets the X value associated with the given Y value.
	 * @param y
	 **/
	inline double convertYtoX( const double& y ) const
	{
		double result = ( y - _b ) / _slope;
		return boundValue( result, _xRange.lowValue(), _xRange.highValue() );
	}

private:

	/**
	 * @brief	boundValue method returns the bounded value based on the
	 *			given high and low values
	 * @param value to be bounded
	 * @param low lowest value "value" can be
	 * @param high highest value "value" can be
	 * @return bounded value
	 */
	inline double boundValue( const double& value, const double& low, const double& high ) const
	{
		if ( value < low )
		{
			return low;
		}

		if ( value > high )
		{
			return high;
		}

		return value;
	}

};


} // namespace Math
} // namespace LibBBB
#endif // LINEARCONVERTER_H
