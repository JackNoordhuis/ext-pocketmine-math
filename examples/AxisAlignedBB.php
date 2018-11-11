<?php
/**
 * Created by IntelliJ IDEA.
 * User: Jack
 * Date: 12/11/18
 * Time: 2:28 AM
 */

$bb = new \pocketmine\math\AxisAlignedBB(-10, -10, -10, 10, 10, 10);

echo $bb . PHP_EOL;

echo $bb->setBounds(0, 0, 0, 10, 10, 10) . PHP_EOL;
echo $bb->addCoord(11, 10, 11) . PHP_EOL;
echo $bb->expand(5, 5, 5) . PHP_EOL;
echo $bb->expandedCopy(10, 15, 20) . PHP_EOL;