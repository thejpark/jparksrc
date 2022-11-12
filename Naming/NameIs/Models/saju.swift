//
//  saju.swift
//  singleview
//
//  Created by Park Jung Gyu on 6/03/2016.
//  Copyright © 2016 pyfamily. All rights reserved.
//

let gan = ["甲", "乙", "丙", "丁", "戊", "己", "庚", "辛", "壬", "癸"]
let ji = ["子", "丑", "寅", "卯", "辰", "巳", "午", "未", "申", "酉", "戌", "亥"]

// need to addjust for new year
let yearStart: Int = 1939 // base year
let monthStart: Int = 12
let ganStartM: Int = 3
let jiStartM: Int = 5

// no need to adjust
let ganStartY: Int = 2
let jiStartY: Int = 8

func getYear(_ year : String, month : String, day : String, time: String) -> String {
    let y = Int(year)
    let diff = y! - yearStart
    let newGan = (ganStartY + diff) % gan.count
    let newJi = (jiStartY + diff) % ji.count
    return gan[newGan] + ji[newJi]
}

func IsLeapyear(_ year : String) -> Bool {
    return IsLeapyear(Int(year)!)
}

func IsLeapyear(_ y: Int) -> Bool {
    if ((y % 4) == 0) {
        return true
    }

    return false
}

func getDaysInYear(_ year: Int) -> Int {
    if IsLeapyear(year) {
        return 366
    }

    return 365
}

func getDaysInMonth(_ month: Int, year: Int) -> Int {
    let m = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

    var r = m[month - 1]
    if IsLeapyear(year) && (month == 2) {
        r += 1
    }

    return r
}

func getDaysLeft(_ day: Int, month: Int, year: Int) -> Int {
    let m = getDaysInMonth(month, year: year)
    var sum = m - day
    var mm = month + 1

    while mm <= 12 {
        sum += getDaysInMonth(mm, year: year)
        mm += 1
    }

    return sum
}

func getDays(_ y1: Int, m1: Int, d1: Int, y2: Int, m2: Int, d2: Int) -> Int {
    let diff_y = y2 - y1
    var sum:Int = 0
    var y = y1
    var m = m1
    var d = d1

    for _ in 0...diff_y {
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

// 2022 jolgi, from sohan
let DefaultJolgi = Jolgi[2023]

func compareNalja(_ a:Nalja, b:Nalja) -> Bool {
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


func getJolgi(_ year: Int) -> [Nalja] {
    if let r = Jolgi[year]{
        return r
    }

    // calculate year if not defined in jolgi
  var r : [Nalja] = DefaultJolgi!
    for y in yearStart + 1...year {
      for i in 0..<DefaultJolgi!.count {
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

func getNyonju(_ year: Int, month: Int, day: Int, hour: Int, minute: Int) -> String {
    let g = gan[(year - 1934) % 10]
    let j = ji[(year - 1936) % 12]
    let g1 = gan[(year - 1935) % 10]
    let j1 = ji[(year - 1937) % 12]

    let jg = getJolgi(year)
    let n : Nalja = (month, day, hour, minute)

    if compareNalja(n, b:jg[1]) {

        return g1 + j1
    }

    return g + j
}

func getWorju(_ year: Int, month: Int, day: Int, hour: Int, minute: Int) -> String{
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
    var diff = year - yearStart
    while (diff > 0) {
        count += 12
        diff -= 1
    }

    count += index
    // 2016.1.5 乙未년 戊子월
    // 2017/1 ( 丙申년 辛丑월 )
    // not sure, but need to adjust
    let g = gan[(6 + count) % 10]
    let j = ji[(count) % 12]

    return g + j
}

var timeDiff : Int {
  var longitude = 126.9780
  if RegisterInfo.obj.longitude != 0 {
    longitude = RegisterInfo.obj.longitude
  }

  var i = -180.0
  let step = 15
  while i < longitude {
    i += 15
  }

  let diff = (i - longitude) * 60.0 / 15.0
  return Int(diff)
}

func getIlju(_ y: Int, m: Int, d: Int, h: Int, mm: Int) -> String {
    var i = getDays(yearStart, m1:monthStart, d1:ganStartM, y2:y, m2:m, d2:d)
    if (h == 0 && timeDiff > 0 && mm < timeDiff) {
        i -= 1
    }

    let gan1 = gan[i % 10]

    i = getDays(yearStart, m1:monthStart, d1:jiStartM, y2:y, m2:m, d2:d)
    if (h == 0 && timeDiff > 0 && mm < timeDiff) {
        i -= 1
    }
    let ji1 = ji[i % 12]

    return gan1 + ji1
}

func getSiju(_ ilgan: Int, hour: Int, minute: Int) -> String {
    let g1 = (ilgan % 5) * 2
    let t = hour * 60 + minute
    var h = [timeDiff, timeDiff + 60]
    for i in 1...11 {
        h.append(timeDiff + 60 + i * 120)
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

func getGan(_ ilju: String) -> Int {
    let i1 = ilju.startIndex
    for i in 0 ... gan.count - 1 {
        let i2 = gan[i].startIndex
        if gan[i][i2] == ilju[i1] {
            return i
        }
    }

    return -1
}

func getSaju(_ year: Int, month: Int, day: Int, hour: Int, minute: Int) -> String
{
    let ilju = getIlju(year, m:month, d:day, h:hour, mm:minute)
    let nyonju = getNyonju(year, month: month, day: day, hour: hour, minute: month)
    let worju = getWorju(year, month: month, day: day, hour: hour, minute: minute)
    let siju = getSiju(getGan(ilju), hour: hour, minute: minute)

    return siju + ilju + worju + nyonju
}


let ganjiohang = ["甲":1, "乙":1, "丙":2, "丁":2, "戊":3, "己":3, "庚":4, "辛":4, "壬":5, "癸":5, "子":5, "丑":3, "寅":1, "卯":1, "辰":3, "巳":2, "午":2, "未":3, "申":4, "酉":4, "戌":3, "亥":5]

// 오행과 그 오행을 돕는 오행들
let helpohang = [1:[1, 5], 2:[1, 2], 3:[2, 3], 4:[3, 4], 5:[4, 5]]

// 오행 한자 매핑
let ohangHanja = [1:"木", 2:"火", 3:"土", 4:"金", 5:"水"]


func getJi(_ j: String) -> Int {
    let j1 = j.index(j.startIndex, offsetBy: 1)
    for i in 0 ... ji.count - 1 {
        let j2 = ji[i].startIndex
        if ji[i][j2] == j[j1] {
            return i
        }
    }

    return -1
}


var sajuohang:[Double] = [0, 0, 0, 0, 0, 0] // first element is not used.

// 신강/신약을 판단하고, 사주의 오행값을 계산함.
func getGangYag(_ year: Int, month: Int, day: Int, hour: Int, minute: Int) -> Double
{
    let ilju = getIlju(year, m:month, d:day, h:hour, mm:minute)
    let nyonju = getNyonju(year, month: month, day: day, hour: hour, minute: month)
    let worju = getWorju(year, month: month, day: day, hour: hour, minute: minute)
    let siju = getSiju(getGan(ilju), hour: hour, minute: minute)

    // clear sajuohang
    for i in 1...5 {
        sajuohang[i] = 0.0
    }
    //

    let base = ganjiohang[gan[getGan(ilju)]]
    var sum: Double = 1.0
    sajuohang[base!] = sajuohang[base!] + 1.0

    if  helpohang[base!]!.contains(ganjiohang[ji[getJi(ilju)]]!) {
        sum += 1.2
    }
    sajuohang[ganjiohang[ji[getJi(ilju)]]!] = sajuohang[ganjiohang[ji[getJi(ilju)]]!] + 1.2

    if helpohang[base!]!.contains(ganjiohang[ji[getJi(siju)]]!) {
        sum += 1.2
    }
    sajuohang[ganjiohang[ji[getJi(siju)]]!] = sajuohang[ganjiohang[ji[getJi(siju)]]!] + 1.2

    if helpohang[base!]!.contains(ganjiohang[ji[getJi(worju)]]!) {
        sum += 3
    }
    sajuohang[ganjiohang[ji[getJi(worju)]]!] = sajuohang[ganjiohang[ji[getJi(worju)]]!] + 3.0


    if helpohang[base!]!.contains(ganjiohang[ji[getJi(nyonju)]]!) {
        sum += 1
    }
    sajuohang[ganjiohang[ji[getJi(nyonju)]]!] = sajuohang[ganjiohang[ji[getJi(nyonju)]]!] + 1.0


    if helpohang[base!]!.contains(ganjiohang[gan[getGan(siju)]]!) {
        sum += 0.8
    }
    sajuohang[ganjiohang[gan[getGan(siju)]]!] = sajuohang[ganjiohang[gan[getGan(siju)]]!] + 0.8

    if helpohang[base!]!.contains(ganjiohang[gan[getGan(worju)]]!) {
        sum += 1
    }
    sajuohang[ganjiohang[gan[getGan(worju)]]!] = sajuohang[ganjiohang[gan[getGan(worju)]]!] + 1.0

    if helpohang[base!]!.contains(ganjiohang[gan[getGan(nyonju)]]!) {
        sum += 0.8
    }
    sajuohang[ganjiohang[gan[getGan(nyonju)]]!] = sajuohang[ganjiohang[gan[getGan(nyonju)]]!] + 0.8

    return sum
}

// 일간을 극 하는 오행
let antiohang = [1:4, 2:5, 3:1, 4:2, 5:3]

//(일간이) 생 하는 오행, 즉 오행과 그 오행이 돕는 오행
let liveohang = [1:2, 2:3, 3:4, 4:5, 5:1]

func getAntiIlgan(_ year: Int, month: Int, day: Int, hour: Int, minute: Int) -> Double
{
    let ilju = getIlju(year, m:month, d:day, h:hour, mm:minute)
    let nyonju = getNyonju(year, month: month, day: day, hour: hour, minute: month)
    let worju = getWorju(year, month: month, day: day, hour: hour, minute: minute)
    let siju = getSiju(getGan(ilju), hour: hour, minute: minute)

    let base = ganjiohang[gan[getGan(ilju)]]
    var sum: Double = 0.0

    if  antiohang[base!] == ganjiohang[ji[getJi(ilju)]]! {
        sum += 1.2
    }

    if antiohang[base!] == ganjiohang[ji[getJi(siju)]]! {
        sum += 1.2
    }

    if antiohang[base!] == ganjiohang[ji[getJi(worju)]]! {
        sum += 3
    }

    if antiohang[base!] == ganjiohang[ji[getJi(nyonju)]]! {
        sum += 1
    }

    if antiohang[base!] == ganjiohang[gan[getGan(siju)]]! {
        sum += 0.8
    }

    if antiohang[base!] == ganjiohang[gan[getGan(worju)]]! {
        sum += 1
    }

    if antiohang[base!] == ganjiohang[gan[getGan(nyonju)]]! {
        sum += 0.8
    }

    return sum
}


func getIlganGangYag(_ year: Int, month: Int, day: Int, hour: Int, minute: Int) -> (Int, Double, Int, Double)
{
    let ilju = getIlju(year, m:month, d:day, h:hour, mm:minute)
    let base = ganjiohang[gan[getGan(ilju)]]
    let strength = getGangYag(year, month: month, day: day, hour: hour, minute: minute)
    let strength2 = getAntiIlgan(year, month: month, day: day, hour: hour, minute: minute)

    return (base!, strength, antiohang[base!]!, strength2)
}


func getHeeYong(_ year: Int, month: Int, day: Int, hour: Int, minute: Int) -> [Int]
{
    let ilju = getIlju(year, m:month, d:day, h:hour, mm:minute)
    let base = ganjiohang[gan[getGan(ilju)]]
    let strength = getGangYag(year, month: month, day: day, hour: hour, minute: minute)
    let anti = getAntiIlgan(year, month: month, day: day, hour: hour, minute: minute)

    if strength < 5 {

        if (anti > 5) {
            var t = base! + 1
            if t > 5 {
                t = 1
            }
            var r: [Int] = helpohang[base!]!
            r.append(t)
            return r
        }
        else {
            return helpohang[base!]!
        }
    }
    else if strength == 5 {
        let worju = getWorju(year, month: month, day: day, hour: hour, minute: minute)
        if  ["巳", "午", "未"].contains(ji[getJi(worju)]) && [1, 2, 3].contains(base!) {
            // summer
            return [4, 5]
        }
        else if ["子", "丑", "亥"].contains(ji[getJi(worju)]) && [3, 4, 5].contains(base!) {
            // winter
            return [1, 2]
        }
        else {
            // find if there is missing ohang in Saju
            var ll:[Int] = []
            if [1, 2].contains(base!) {
                ll = [3, 4, 5]
            }
            else if [4, 5].contains(base!) {
                ll = [1, 2, 3]
            }
            else {
                ll = [1, 2, 4, 5]
            }

            ll.sort(by: {sajuohang[$0] < sajuohang[$1]})

            return [ll[0], ll[1]]
        }

    }
    else {
        if base == 5 {
            return [1, 2, 3]
        }
        else if base == 4 {
            return [1, 2]
        }
        else if base == 3 {
            return [1]
        }
        else if base == 2  {
            return [4, 5]
        }
        else if base == 1 {
            return [4, 5]
        }
        else {
            // should not reach here
            return []
        }
    }
}

func getBarumOhangIndex(_ str: String) -> Int {
    if barum_1.contains(str) {
        return 1
    }
    else if barum_2.contains(str) {
        return 2
    }
    else if barum_3.contains(str) {
        return 3
    }
    else if barum_4.contains(str) {
        return 4
    }
    else if barum_5.contains(str) {
        return 5
    }

    return 0
}

let barum_1 = ["가","각","간","갈","감","갑","강","개","객","갱","갹","거","건","걸","검","겁","게","격","견","결","겸","경","계","고","곡","곤","골","공","곶","과","곽","관","괄","광","괘","괴","괵","굉","교","구","국","군","굴","궁","권","궐","궤","귀","규","균","귤","극","근","글","금","급","긍","기","긴","길","김","끽","쾌"]

let barum_2 = ["나","낙","난","날","남","납","낭","내","녀","녁","년","념","녑","녕","노","농","뇌","뇨","누","눈","눌","뉴","뉵","능","니","닉","닐","다","단","달","담","답","당","대","댁","덕","도","독","돈","돌","동","두","둔","둘","득","등","라","락","란","랄","람","랍","랑","래","랭","략","량","려","력","련","렬","렴","렵","령","례","로","록","론","롱","뢰","료","룡","루","류","륙","륜","률","륭","륵","름","릉","리","린","림","립","타","탁","탄","탈","탐","탑","탕","태","택","탱","터","토","톤","통","퇴","투","퉁","특","틈"]

let barum_3 = ["아","악","안","알","암","압","앙","애","액","앵","야","약","양","어","억","언","얼","엄","업","에","엔","여","역","연","열","염","엽","영","예","오","옥","온","올","옹","와","완","왈","왕","왜","외","요","욕","용","우","욱","운","울","웅","원","월","위","유","육","윤","율","융","은","을","음","읍","응","의","이","익","인","일","임","입","잉","하","학","한","할","함","합","항","해","핵","행","향","허","헌","헐","험","혁","현","혈","혐","협","형","혜","호","혹","혼","홀","홍","화","확","환","활","황","회","획","횡","효","후","훈","훌","훙","훤","훼","휘","휴","휼","흉","흑","흔","흘","흠","흡","흥","희","힐"]

let barum_4 = ["사","삭","산","살","삼","삽","상","새","색","생","서","석","선","설","섬","섭","성","세","소","속","손","솔","송","쇄","쇠","수","숙","순","술","숭","쉬","슬","습","승","시","식","신","실","심","십","쌍","씨","자","작","잔","잠","잡","장","재","쟁","저","적","전","절","점","접","정","제","조","족","존","졸","종","좌","죄","주","죽","준","줄","중","즉","즐","즙","증","지","직","진","질","짐","집","징","차","착","찬","찰","참","창","채","책","처","척","천","철","첨","첩","청","체","초","촉","촌","총","촬","최","추","축","춘","출","충","췌","취","측","층","치","칙","친","칠","침","칩","칭"]

let barum_5 = ["마","막","만","말","망","매","맥","맹","멱","면","멸","명","몌","모","목","몰","몽","묘","무","묵","문","물","미","민","밀","박","반","발","방","배","백","번","벌","범","법","벽","변","별","병","보","복","본","볼","봉","부","북","분","불","붕","비","빈","빙","파","판","팔","패","팽","퍅","편","폄","평","폐","포","폭","표","품","풍","피","픽","필","핍"]
