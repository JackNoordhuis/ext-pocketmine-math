<?php
/**
 * Generated stub file for code completion purposes
 */

namespace pocketmine\math {
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
	public const ALL = array (
  0 => 0,
  1 => 1,
  2 => 2,
  3 => 3,
  4 => 4,
  5 => 5,
);
	public const HORIZONTAL = array (
  0 => 2,
  1 => 3,
  2 => 4,
  3 => 5,
);

	public static function axis(int $direction) : int{}

	public static function isPositive(int $direction) : bool{}

	public static function opposite(int $direction) : int{}

	public static function rotate(int $direction, int $axis, bool $clockwise) : int{}

	public static function validate(int $facing) : void{}
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

	public function normalize() : float{}

	public function dot(\pocketmine\math\Vector2 $v) : float{}

	public function __toString() : string{}
}
}
