<?php
/**
 * Created by IntelliJ IDEA.
 * User: Jack
 * Date: 4/11/18
 * Time: 10:37 PM
 */

$vec = new \pocketmine\math\Vector2(mt_rand(-99, 99) + (mt_rand(-99, 99) / 10), mt_rand(-99, 99) + (mt_rand(-99, 99) / 10));

echo $vec->getX() . PHP_EOL;
echo $vec->getY() . PHP_EOL;

echo $vec->getFloorX() . PHP_EOL;
echo $vec->getFloorY() . PHP_EOL;

echo $vec->add(0.5, 0.5) . PHP_EOL;
echo $vec->subtract(0.5, 0.5) . PHP_EOL;

echo $vec->ceil() . PHP_EOL;
echo $vec->floor() . PHP_EOL;
echo $vec->round() . PHP_EOL;
echo $vec->abs() . PHP_EOL;
echo $vec->multiply(2) . PHP_EOL;
echo $vec->divide(2) . PHP_EOL;

echo $vec->distance(0, 0) . PHP_EOL;
echo $vec->distanceSquared(0, 0) . PHP_EOL;

echo $vec->normalize() . PHP_EOL;

echo $vec->dot($vec->multiply(2)) . PHP_EOL;

echo $vec . PHP_EOL;