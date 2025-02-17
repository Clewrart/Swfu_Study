/*
 Navicat Premium Data Transfer

 Source Server         : Clewrart_Server
 Source Server Type    : MySQL
 Source Server Version : 80402
 Source Host           : 47.96.10.165:3306
 Source Schema         : softSys

 Target Server Type    : MySQL
 Target Server Version : 80402
 File Encoding         : 65001

 Date: 21/12/2024 12:24:29
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for car_table
-- ----------------------------
DROP TABLE IF EXISTS `car_table`;
CREATE TABLE `car_table`  (
  `id` int NOT NULL AUTO_INCREMENT COMMENT '车辆id，pk',
  `carnum` text CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '车牌，地X·123456',
  `for_userid` int NOT NULL COMMENT '车辆归属用户',
  `cartype` text CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '车辆类型（颜色）',
  `status` int NOT NULL DEFAULT 0 COMMENT '车辆状态，默认0无操作，1已停车，2已预约，3报警',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `fk_for_userid`(`for_userid` ASC) USING BTREE,
  CONSTRAINT `useridfk` FOREIGN KEY (`for_userid`) REFERENCES `user_table` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 21 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Table structure for location
-- ----------------------------
DROP TABLE IF EXISTS `location`;
CREATE TABLE `location`  (
  `id` int NOT NULL AUTO_INCREMENT COMMENT '车位编号，pk',
  `parknum` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL DEFAULT '0' COMMENT '停车场编号',
  `position_lat` decimal(9, 6) NOT NULL COMMENT '纬度,XXX.xxxxxx',
  `position_lng` decimal(9, 6) NOT NULL COMMENT '经度,XXX.xxxxxx',
  `status` smallint NOT NULL DEFAULT 0 COMMENT '车位状态，默认0空闲，1占用，2预约，3警报',
  `for_carid` int NULL DEFAULT NULL COMMENT '当前车位占用车辆（存车辆id）',
  `warn_time` datetime NULL DEFAULT NULL COMMENT '告警时间',
  `address` text CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '车位地址人话描述',
  `numinpark` varchar(6) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '场内编号',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `position`(`position_lat` ASC) USING BTREE,
  INDEX `fk_for_carid`(`for_carid` ASC) USING BTREE,
  CONSTRAINT `caridpk` FOREIGN KEY (`for_carid`) REFERENCES `car_table` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 47 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Table structure for manager
-- ----------------------------
DROP TABLE IF EXISTS `manager`;
CREATE TABLE `manager`  (
  `id` int NOT NULL AUTO_INCREMENT COMMENT '管理员id，pk',
  `manage_num` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '管理员账号',
  `password` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '管理员密码',
  `manage_name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '管理员姓名',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `manage_num`(`manage_num` ASC) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 3 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Table structure for reserve_table
-- ----------------------------
DROP TABLE IF EXISTS `reserve_table`;
CREATE TABLE `reserve_table`  (
  `id` int NOT NULL AUTO_INCREMENT COMMENT '预约号，pk',
  `expire_time` datetime NOT NULL COMMENT '预约时间',
  `for_carid` int NOT NULL COMMENT '预约车辆',
  `for_locationid` int NOT NULL COMMENT '预约车位号',
  `status` smallint NOT NULL DEFAULT 1 COMMENT '预约信息状态，0为失效，1为有效',
  `for_userid` int NOT NULL COMMENT '预约信息归属用户id',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `fk_reserve_carid`(`for_carid` ASC) USING BTREE,
  INDEX `fk_reserve_locationid`(`for_locationid` ASC) USING BTREE,
  INDEX `uidfk`(`for_userid` ASC) USING BTREE,
  CONSTRAINT `caridfk` FOREIGN KEY (`for_carid`) REFERENCES `car_table` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `cwfk` FOREIGN KEY (`for_locationid`) REFERENCES `location` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `uidfk` FOREIGN KEY (`for_userid`) REFERENCES `user_table` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 26 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Table structure for user_table
-- ----------------------------
DROP TABLE IF EXISTS `user_table`;
CREATE TABLE `user_table`  (
  `id` int NOT NULL AUTO_INCREMENT COMMENT '用户id，pk',
  `username` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '用户名',
  `phonenum` varchar(11) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '用户电话',
  `password` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '用户密码',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `phonenum`(`phonenum` ASC) USING BTREE,
  UNIQUE INDEX `phonenum_2`(`phonenum` ASC) USING BTREE,
  UNIQUE INDEX `phonenum_3`(`phonenum` ASC) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 14 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = DYNAMIC;

SET FOREIGN_KEY_CHECKS = 1;
