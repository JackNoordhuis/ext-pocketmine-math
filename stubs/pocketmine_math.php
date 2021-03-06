<?php
/**
 * Generated stub file for code completion purposes
 */

namespace pocketmine\math {
class AxisAlignedBB{
	public $minX;
	public $minY;
	public $minZ;
	public $maxX;
	public $maxY;
	public $maxZ;

	public function __construct(float $minX, float $minY, float $minZ, float $maxX, float $maxY, float $maxZ){}

	public function setBounds(float $minX, float $minY, float $minZ, float $maxX, float $maxY, float $maxZ) : \pocketmine\math\AxisAlignedBB{}

	public function setBB(\pocketmine\math\AxisAlignedBB $bb) : \pocketmine\math\AxisAlignedBB{}

	public function addCoord(float $x, float $y, float $z) : \pocketmine\math\AxisAlignedBB{}

	public function expand(float $x, float $y, float $z) : \pocketmine\math\AxisAlignedBB{}

	public function expandedCopy(float $x, float $y, float $z) : \pocketmine\math\AxisAlignedBB{}

	public function offset(float $x, float $y, float $z) : \pocketmine\math\AxisAlignedBB{}

	public function offsetCopy(float $x, float $y, float $z) : \pocketmine\math\AxisAlignedBB{}

	public function contract(float $x, float $y, float $z) : \pocketmine\math\AxisAlignedBB{}

	public function contractedCopy(float $x, float $y, float $z) : \pocketmine\math\AxisAlignedBB{}

	public function calculateXOffset(\pocketmine\math\AxisAlignedBB $bb, float $x) : float{}

	public function calculateYOffset(\pocketmine\math\AxisAlignedBB $bb, float $y) : float{}

	public function calculateZOffset(\pocketmine\math\AxisAlignedBB $bb, float $z) : float{}

	public function intersectsWith(\pocketmine\math\AxisAlignedBB $bb, float $epsilon = null) : bool{}

	public function isVectorInside(\pocketmine\math\Vector3 $bb) : bool{}

	public function getAverageEdgeLength() : float{}

	public function isVectorInYZ(\pocketmine\math\Vector3 $bb) : bool{}

	public function isVectorInXZ(\pocketmine\math\Vector3 $bb) : bool{}

	public function isVectorInXY(\pocketmine\math\Vector3 $bb) : bool{}

	public function calculateIntercept(\pocketmine\math\Vector3 $pos1, \pocketmine\math\Vector3 $pos2) : \pocketmine\math\RayTraceResult{}

	public function __toString() : string{}
}

class Bearing{
	public const SOUTH = 0;
	public const WEST = 1;
	public const NORTH = 2;
	public const EAST = 3;

	public static function toFacing(int $bearing) : int{}

	public static function fromFacing(int $facing) : int{}

	public static function fromAngle(float $angle) : int{}

	public static function rotate(int $bearing, int $step) : int{}

	public static function opposite(int $bearing) : int{}
}

class Facing{
	public const AXIS_Y = 0;
	public const AXIS_Z = 1;
	public const AXIS_X = 2;
	public const FLAG_AXIS_POSITIVE = 1;
	public const DOWN = 0;
	public const UP = 1;
	public const NORTH = 2;
	public const SOUTH = 3;
	public const WEST = 4;
	public const EAST = 5;

	public static function axis(int $direction) : int{}

	public static function isPositive(int $direction) : bool{}

	public static function opposite(int $direction) : int{}

	public static function rotate(int $direction, int $axis, bool $clockwise) : int{}

	public static function validate(int $facing) : void{}
}

class Math{

	public static function floorFloat(float $n) : int{}

	public static function ceilFloat(float $n) : int{}

	public static function solveQuadratic(float $a, float $b, float $c) : array{}
}

class RayTraceResult{
	public $bb;
	public $hitFace;
	public $hitVector;

	public function __construct(\pocketmine\math\AxisAlignedBB $bb, int $hitface, \pocketmine\math\Vector3 $hitVector){}

	public function getBoundingBox() : \pocketmine\math\AxisAlignedBB{}

	public function getHitFace() : int{}

	public function getHitVector() : \pocketmine\math\Vector3{}
}

class Vector2{
	public $x;
	public $y;

	public function __construct(float $x = null, float $y = null){}

	public function getX() : float{}

	public function getY() : float{}

	public function getFloorX() : int{}

	public function getFloorY() : int{}

	public function add($x, float $y = null) : \pocketmine\math\Vector2{}

	public function subtract($x, float $y = null) : \pocketmine\math\Vector2{}

	public function ceil() : \pocketmine\math\Vector2{}

	public function floor() : \pocketmine\math\Vector2{}

	public function round() : \pocketmine\math\Vector2{}

	public function abs() : \pocketmine\math\Vector2{}

	public function multiply(float $number) : \pocketmine\math\Vector2{}

	public function divide(float $number) : \pocketmine\math\Vector2{}

	public function distance($x, float $y = null) : float{}

	public function distanceSquared($x, float $y = null) : float{}

	public function length() : float{}

	public function lengthSquared() : float{}

	public function normalize() : \pocketmine\math\Vector2{}

	public function dot(\pocketmine\math\Vector2 $v) : float{}

	public function __toString() : string{}
}
}
