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



/*
2016년 양력 입춘(立春)02월 04일 18시 48분 (음력 입춘(立春)2015년 12월 26일)
2017년 양력 입춘(立春)02월 04일 00시 34분 (음력 입춘(立春)2017년 01월 08일)
2018년 양력 입춘(立春)02월 04일 06시 24분 (음력 입춘(立春)2017년 12월 19일)
2019년 양력 입춘(立春)02월 04일 12시 13분 (음력 입춘(立春)2018년 12월 30일)
2020년 양력 입춘(立春)02월 04일 18시 07분 (음력 입춘(立春)2020년 01월 21일)
*/

/*
365.2422
360
*/


/*
gongjeonjoogi 365.2422
360
let x = 0.2422 * 60.0 * 24.0
let h = Int(x / 60.0)
let m = Int (x - Double(h * 60))
5h.48m
*/

// month, day, hour, minute
typealias Nalja = (Int, Int, Int, Int)
// 2016 jolgi, from sohan
let Jolgi : [Nalja] = [(1, 6, 7, 8), (2,4,18,46), (3,5,12,43),(4,4,17,27), (5, 5, 10, 42), (6, 5, 14, 48),
    (7, 7, 1, 3), (8, 7, 10, 53), (9,7,13,51), (10,8,5,33), (11,7,8,48), (12,7,1,41)]

func compareNalja(a:Nalja, b:Nalja) -> Bool {
    
    if (b.0 > a.0) {
        return true
    }
    else if (b.0 < a.0) {
        return false
    }
    
    if (b.1 > a.1) {
        return true
    }
    else if (b.1 < a.1) {
        return false
    }
    
    if (b.2 > a.2) {
        return true
    }
    else if (b.2 < a.2) {
        return false
    }
    
    if (b.3 > a.3) {
        return true
    }
    else if (b.3 < a.3) {
        return false
    }
    
    return false
}

let base_year = 2016
func getJolgi(year: Int) -> [Nalja] {
    
    var r : [Nalja] = Jolgi

    if year == base_year {
        return r
    }
    
    for y in base_year + 1...year {
        for i in 0..<Jolgi.count {
            let m = r[i].3 + 48
            if m >= 60 {
                r[i].2 += 1
            }
            r[i].3 = m % 60
            
            let h = r[i].2 + 5
            if h >= 24 {
                r[i].1 += 1
            }
            r[i].2 = h % 24
            
            if IsLeapyear(y - 1) && i == 0 {
                r[i].1 -= 1
            }
            if IsLeapyear(y - 1) && i == 1 {
                r[i].1 -= 1
            }
            if IsLeapyear(y) {
                if !(i == 0 || i == 1) {
                    r[i].1 -= 1
                }
            }
            
        }
    }
    
    return r
}

func getNyonju(year: Int, month: Int, day: Int, hour: Int, minute: Int) -> String {
    
    let g = gan[(year - 2014) % 10]
    let j = ji[(year - 2008) % 12]
    let g1 = gan[(year - 2015) % 10]
    let j1 = ji[(year - 2009) % 12]
    
    let jg = getJolgi(year)
    let n : Nalja = (month, day, hour, minute)
    
    if compareNalja(n, b:jg[1]) {
        
        return g1 + j1
    }
    
    return g + j
}

func getWorju(year: Int, month: Int, day: Int, hour: Int, minute: Int) -> String{
    let d: Nalja = (month, day, hour, minute)
    let jolgi = getJolgi(year)
    
    var index = 0 // or 12?
    for i in 0..<jolgi.count {
        if compareNalja(d, b: jolgi[i]) {
            index = i
            break
        }
    }
    
    var count = 0
    // 2016.1.5 乙未년 戊子월
    
    var diff = year - base_year
    while (diff > 0) {
        count += 12
        diff -= 1
    }

    count += index
    let g = gan[(4 + count) % 10]
    let j = ji[count % 12]
    
    return g + j
}


func getIlju(y: Int, m: Int, d: Int) -> String {
    
    
    var i = getDays(2016, m1:3, d1:3, y2:y, m2:m, d2:d)
    let gan1 = gan[i % 10]
    
    i = getDays(2016, m1:3, d1:7, y2:y, m2:m, d2:d)
    let ji1 = ji[i % 12]
    
    return gan1 + ji1
}


func getSiju(ilgan: Int, hour: Int, minute: Int) -> String {
    let g1 = (ilgan % 5) * 2
    let t = hour * 60 + minute
    var h = [30, 90]
    for i in 1...11 {
        h.append(90 + i * 120)
    }
    h.append(24 * 60)
    
    var index = 0
    for i in 0...(h.count - 1) {
        if t < h[i] {
            index = i
            break
        }
    }
    
    if index == 0 {
        let g = gan[(g1 + index + 2) % 10]
        let j = ji[0]
        return g + j
        
    }
    else {
        let g = gan[(g1 + index - 1) % 10]
        let j = ji[(index - 1) % 12]
        return g + j
    }
}

func getGan(ilju: String) -> Int {
    let i1 = ilju.startIndex
    for i in 0 ... gan.count - 1 {
        let i2 = gan[i].startIndex
        if gan[i].characters[i2] == ilju.characters[i1] {
            return i
        }
    }
    
    return -1
}


func getSaju(year: Int, month: Int, day: Int, hour: Int, minute: Int) -> String
{
    let ilju = getIlju(year, m:month, d:day)
    let nyonju = getNyonju(year, month: month, day: day, hour: hour, minute: month)
    let worju = getWorju(year, month: month, day: day, hour: hour, minute: minute)
    let siju = getSiju(getGan(ilju), hour: hour, minute: minute)
    
    return nyonju + worju + ilju + siju
}


let ganjiohang = ["甲":1, "乙":1, "丙":2, "丁":2, "戊":3, "己":3, "庚":4, "辛":4, "壬":5, "癸":5, "子":5, "丑":3, "寅":1, "卯":1, "辰":3, "巳":2, "午":2, "未":3, "申":4, "酉":4, "戌":3, "亥":5]

let helpohang = [1:(1, 5), 2:(1, 2), 3:(2, 3), 4:(3, 4), 5:(4, 5)]


func getJi(j: String) -> Int {
    let j1 = j.startIndex.advancedBy(1)
    for i in 0 ... ji.count - 1 {
        let j2 = ji[i].startIndex
        if ji[i].characters[j2] == j.characters[j1] {
            return i
        }
    }
    
    return -1
}


func getGangYag(year: Int, month: Int, day: Int, hour: Int, minute: Int) -> Double
{
    let ilju = getIlju(year, m:month, d:day)
    let nyonju = getNyonju(year, month: month, day: day, hour: hour, minute: month)
    let worju = getWorju(year, month: month, day: day, hour: hour, minute: minute)
    let siju = getSiju(getGan(ilju), hour: hour, minute: minute)
    
    let base = ganjiohang[gan[getGan(ilju)]]
    var sum: Double = 0
    
    if base == ganjiohang[ji[getJi(ilju)]] {
        sum += 1.2
    }
    
    if base == ganjiohang[ji[getJi(siju)]] {
        sum += 1.2
    }
    
    if base == ganjiohang[ji[getJi(worju)]] {
        sum += 3
    }
    
    if base == ganjiohang[ji[getJi(nyonju)]] {
        sum += 1
    }
    
    if base == ganjiohang[gan[getGan(siju)]] {
        sum += 0.8
    }
    
    if base == ganjiohang[gan[getGan(worju)]] {
        sum += 1
    }
    
    if base == ganjiohang[gan[getGan(nyonju)]] {
        sum += 0.8
    }
    
    return sum
}

