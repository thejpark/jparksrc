//
//  saju.swift
//  singleview
//
//  Created by Park Jung Gyu on 6/03/2016.
//  Copyright © 2016 pyfamily. All rights reserved.
//

import Foundation



let gan = ["甲", "乙", "丙", "丁", "戊", "己", "庚", "辛", "壬", "癸"]
let ji = ["子", "丑", "寅", "卯", "辰", "巳", "午", "未", "申", "酉", "戌", "亥"]

let yearStart: Int = 2016
let monthStart: Int = 3

let ganStartY: Int = 2
let jiStartY: Int = 8

let ganStartM: Int = 7
let jiStartM: Int = 3

func getYear(year : String, month : String, day : String, time: String) -> String {
    let y = Int(year)
    let diff = y! - yearStart
    let newGan = (ganStartY + diff) % gan.count
    let newJi = (jiStartY + diff) % ji.count
    return gan[newGan] + ji[newJi]
}

func IsLeapyear(year : String) -> Bool {
    return IsLeapyear(Int(year)!)
}

func IsLeapyear(y: Int) -> Bool {
    if ((y % 4) == 0) {
        return true
    }
    
    return false
}


func getDaysInYear(year: Int) -> Int {
    
    if IsLeapyear(year) {
        return 366
    }
    
    return 365
}

func getDaysInMonth(month: Int, year: Int) -> Int {
    
    let m = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    
    var r = m[month - 1]
    if IsLeapyear(year) && (month == 2) {
        r += 1
    }
    
    return r
}

func getDaysLeft(day: Int, month: Int, year: Int) -> Int {
    
    let m = getDaysInMonth(month, year: year)
    var sum = m - day
    var mm = month + 1
    
    while mm <= 12 {
        sum += getDaysInMonth(mm, year: year)
        mm += 1
    }
    
    return sum
}


func getDays(y1: Int, m1: Int, d1: Int, y2: Int, m2: Int, d2: Int) -> Int {
    
    let diff_y = y2 - y1
    
    var sum:Int = 0
    
    var y = y1
    var m = m1
    var d = d1
    
    for i in 0...diff_y {
        sum += getDaysLeft(d, month: m, year: y)
        y = y + 1
        d = 0
        m = 1
    }
    
    sum -=  getDaysLeft(d2, month: m2, year: y2)
    
    return sum
}


func getIlju(y: Int, m: Int, d: Int) -> String {
    
    
    var i = getDays(2016, m1:3, d1:3, y2:y, m2:m, d2:d)
    let gan1 = gan[i % 10]
    
    i = getDays(2016, m1:3, d1:7, y2:y, m2:m, d2:d)
    let ji1 = ji[i % 12]
    
    return gan1 + ji1
}






