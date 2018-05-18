/*
 * Licensed under the 'LICENSE'.
 * See LICENSE file in the project root for full license information.
 */
#ifndef RANGE_H
#define RANGE_H

namespace LibBBB {
namespace Math {

/**
 * @brief	The Range class wraps the high and low values, and, upon construction,
 *			calculates the range.
 */
template< typename DataType >
class Range
{
private:

	const DataType _low;
	const DataType _high;
	const DataType _range;

public:

	Range( const DataType& lowValue, const DataType& highValue )
		: _low( lowValue )
		, _high( highValue )
		, _range( highValue - ( lowValue + 1 ) )
	{}

	~Range() {}

	/**
	 * @brief highValue getter
	 * @return high value
	 */
	DataType highValue() const
	{
		return _high;
	}

	/**
	 * @brief lowValue getter
	 * @return low value
	 */
	DataType lowValue() const
	{
		return _low;
	}

	/**
	 * @brief range getter
	 * @return range
	 */
	DataType range() const
	{
		return _range;
	}
};

} // namespace Math
} // namespace LibBBB
#endif // RANGE_H
