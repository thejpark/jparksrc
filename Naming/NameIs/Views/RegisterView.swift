//
//  RegisterView.swift
//  NewFeatures
//
//  Created by Jung Gyu Park on 13/6/2022.
//

import SwiftUI
import PhotosUI
import CoreLocation
import GoogleMobileAds

//struct TextEditingView: View {
//  @State private var fullText: String = ""
//  let placeholderString : String = "태명을 지어주세요"
//
//  var body: some View {
////    VStack {
//    HStack(spacing: base * 3) {
////          Image(image)
////            .frame(width: base * 6, height: base * 6)
////      Text("태명")
////        .lineLimit(1).foregroundColor(.black)
//      TextEditor(text: self.$fullText)
//        .onAppear(perform: {
//          if self.fullText.isEmpty {
//            self.fullText = placeholderString
//          }
//        })
//        .foregroundColor(self.fullText == placeholderString ? .gray : .primary)
//        .onTapGesture(perform: {
//          if self.fullText == placeholderString {
//              self.fullText = ""
//          }})
//    }
//    .frame(height: base * 14)
//    .padding(.horizontal, base * 3)
////  }
//  }
//}


private let base: CGFloat = 4.0

struct FamilynameComponent: View {
  @State private var familyName: String = RegisterInfo.obj.surName
  @State private var selectedSurnameIndex = 0

  var body: some View {
//    VStack {
//      Button {
//        viewModel.editPressed(action: item.action)
//      } label: {
      let binding = Binding(
        get: { self.selectedSurnameIndex },
        set: { self.selectedSurnameIndex = $0
        }
       )

      HStack(spacing: base * 3) {
//          Image(image)
//            .frame(width: base * 6, height: base * 6)
          Text("성씨")
            .lineLimit(1).foregroundColor(.black)
          Spacer()
          Spacer()
          Spacer()
          Spacer()
          Spacer()
          TextField("성을 한글로 입력하세요", text: $familyName)
            .lineLimit(1).foregroundColor(.blue)

          //          Spacer()
          let pickerData = getLastNameFromHangul(familyName)
//          hanjaSurname = pickerData
          if pickerData.count == 1 {
            Text(onChangeLastName(n: familyName, h: pickerData[0], s: pickerData[0]))
            Spacer()
            Spacer()

          }
          else if pickerData.count > 1 {
            Picker("", selection: binding, content: {
              ForEach(0..<pickerData.count, content: {index in //
                Text(onChangeLastName(n: familyName, h: pickerData[index], s: pickerData[selectedSurnameIndex]))
//                Text(pickerData[index])
              })
            })
//            Text("Selected Surname: \(pickerData[selectedSurnameIndex])")
            Spacer()
            Spacer()
          }
        }
        .frame(height: base * 10)
        .padding(.horizontal, base * 3)
//      }
//    }
  }

//  var text: String
//  var image: String
}

var pendingRegisterInfo = RegisterInfo.obj
//var pendingRegisterInfo = RegisterInfo(
//  surName: RegisterInfo.obj.surName,
//  surNameHanja: RegisterInfo.obj.surNameHanja,
//  gender: RegisterInfo.obj.gender,
//  datetime: RegisterInfo.obj.datetime,
//  birthPlace: RegisterInfo.obj.birthPlace,
//  latitude: RegisterInfo.obj.latitude,
//  longitude: RegisterInfo.obj.longitude,
//  image: RegisterInfo.obj.image)

//
func onChangeGender(g: Gender) {
  pendingRegisterInfo.gender = g
}

func onChangeDate(d: Date) {
  pendingRegisterInfo.datetime = d
}

func onChangeLastName(n: String, h: String, s: String) -> String {
  pendingRegisterInfo.surName = n
  pendingRegisterInfo.surNameHanja = s
  return h
}

struct GenderComponent: View {
  @State private var selectedGender: Gender = RegisterInfo.obj.gender
//  @State var selectedGender: Gender
  var body: some View {
//    VStack {
//      Button {
////        viewModel.editPressed(action: item.action)
//      } label: {
        let binding = Binding(
          get: { self.selectedGender },
          set: { self.selectedGender = $0
            onChangeGender(g: $0)
          }
         )
        HStack(spacing: base * 3) {
//          Image(image)
//            .frame(width: base * 6, height: base * 6)
          Text("성별")
            .lineLimit(1).foregroundColor(.black)
          Spacer()
          Picker("성별", selection: binding) {
            Text("여").tag(Gender.female)
            Text("남").tag(Gender.male)
          }

          Spacer()
          Spacer()
        }
        .frame(height: base * 10)
        .padding(.horizontal, base * 3)
    }
}


struct DobComponent: View {
  @State private var date = RegisterInfo.obj.datetime
  let dateRange: ClosedRange<Date> = {
      let calendar = Calendar.current
      let startComponents = DateComponents(year: 1940, month: 1, day: 1)
      let endComponents = DateComponents(year: 2023, month: 12, day: 31, hour: 23, minute: 59, second: 59)
      return calendar.date(from:startComponents)!
          ...
          calendar.date(from:endComponents)!
  }()
  var body: some View {
//    VStack {
//      Button {
////        viewModel.editPressed(action: item.action)
//      } label: {

        let binding = Binding(
          get: { self.date },
          set: { self.date = $0
            onChangeDate(d: $0)
          }
         )

    HStack(spacing: base * 3) {
//          Image(image)
//            .frame(width: base * 6, height: base * 6)
          Text("생일")
            .lineLimit(1).foregroundColor(.black)
//          Spacer()
          DatePicker(
              "",
               selection: binding,
               in: dateRange,
               displayedComponents: [.date, .hourAndMinute]
          )
          Spacer()
        }
        .frame(height: base * 10)
        .padding(.horizontal, base * 3)

  }
//  }

}

struct PlaceComponent: View {
  @State private var currentLocation: String = RegisterInfo.obj.birthPlace
  let locationProvider: ProvidesCurrentLocationProvider = CurrentLocationProvider()
  var body: some View {
    VStack {
//      Button {
////        viewModel.editPressed(action: item.action)
//      } label: {

        HStack(spacing: base * 2) {
//          Image(image)
//            .frame(width: base * 6, height: base * 6)
          Text("출생지")
            .lineLimit(1).foregroundColor(.black)
          Spacer()
          Text(currentLocation)
            .lineLimit(1).foregroundColor(.black)

          Spacer()
          Spacer()
        }
        .frame(height: base * 10)
        .padding(.horizontal, base * 3)

        NavigationLink {
          CoordinateInputView()
        } label: {
          Text("출생지 변경")
        }
    }.onAppear() {
      populateLocation()
    }
  }

  func populateLocation() {
    if pendingRegisterInfo.latitude == 0 && pendingRegisterInfo.longitude == 0 {
      getCurrentLocation { location in
        guard let location = location
        else { return }
        self.currentLocation = location.name
        pendingRegisterInfo.birthPlace = location.name
        pendingRegisterInfo.latitude = location.latitude
        pendingRegisterInfo.longitude = location.longitude
      }
    } else {
      let geoLocation = GeoLocation(latitude: pendingRegisterInfo.latitude,
                                        longitude: pendingRegisterInfo.longitude,
                                        accuracy: kCLLocationAccuracyBest)
      ReverseGeocoder.reverseGeocodeLocation(withCoordinate: geoLocation) { location in
          guard let location = location
          else { return }
          self.currentLocation = location.name
          pendingRegisterInfo.birthPlace = location.name
        }
    }
  }

  func getCurrentLocation(_ completion: @escaping (GeoLocation?) -> Void) {
    locationProvider.getCurrentLocation { result in
      switch result {
      case .updatedLocation(let currentLocation):
        guard let currentLocation = currentLocation else {
          completion(nil)
          return
        }
        ReverseGeocoder.reverseGeocodeLocation(withCoordinate: currentLocation) { location in
          completion(location)
        }
      case .deniedAccess, .error:
        completion(nil)
      }
    }
  }

}

struct RegisterView: View {
  @State private var showingPopover = false
  @State private var showingOk = false
  @State private var showingReinstall = false
  @State private var selectedItem: PhotosPickerItem?
  @State private var selectedImage: Image = getRegisteredImage()

  private let coordinator = InterstitialAdCoordinator()
  private let adViewControllerRepresentable = AdViewControllerRepresentable()

  var adViewControllerRepresentableView: some View {
    adViewControllerRepresentable
      .frame(width: .zero, height: .zero)
  }

  var body: some View {
    Group {
      ScrollView {
        VStack(alignment: .leading) {
          selectedImage
            .resizable()
            .aspectRatio(contentMode: .fit)
            .frame(height: 300)
            .padding([.top, .leading, .trailing], 40.0)
            .padding(.bottom, 20.0)
          //          if let selectedImage {
//            selectedImage
//              .resizable()
//              .aspectRatio(contentMode: .fit)
//          } else {
//            Image("sunny")
//              .resizable()
//              .aspectRatio(contentMode: .fit)
//          }

          HStack() {
            Spacer()
            PhotosPicker(selection: $selectedItem, matching: .images) {
              Label("사진 변경", systemImage: "photo")
            }
            .tint(.purple)
            .controlSize(.large)
            .buttonStyle(.borderedProminent)
            .onChange(of: selectedItem) { newValue in
              Task {
                if let imageData = try? await newValue?.loadTransferable(type: Data.self), let image = UIImage(data: imageData) {
                  selectedImage = Image(uiImage: image)
                  setRegisteredImage(selectedImage)
                  pendingRegisterInfo.image = imageData
                }
              }
            }
            Spacer()
          }

          Divider()
            .background(.black)

          FamilynameComponent()
          Divider()
            .background(.black)

          GenderComponent()
          Divider()
            .background(.black)

          DobComponent()

          Divider()
            .background(.black)

          PlaceComponent()
        }
//        .padding(.top, 10)
        .padding(.leading, 20)
        .padding(.trailing, 20)
        .padding(.bottom, 40)
      }
    }
    .background(adViewControllerRepresentableView)
    .navigationBarItems(
//      leading: Button("취소", action: cancelRegister)kkk
//        .foregroundColor(Colors.Accent.Content.primary),
      leading: NavigationLink("도움말", destination: FeaturesView()),
      trailing: Button("저장") {
//        let urlToDocumentsFolder: URL? = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).last
//        let installDate = try? FileManager.default.attributesOfItem(atPath: (urlToDocumentsFolder?.path)!)[.creationDate] as? Date
//        let currentDate = Date()
//        var timeInterval: TimeInterval = 0
//        if installDate != nil {
//          timeInterval = currentDate.timeIntervalSince(installDate!)
//        }

        if (pendingRegisterInfo.surName == "" || pendingRegisterInfo.surNameHanja == "" || pendingRegisterInfo.birthPlace == "") {
          showingPopover = true
//        } else if timeInterval > 60 * 60 * 24 * 30 {
//          showingReinstall = true
        } else {
          showingOk = true
//          register()
//          coordinator.showAd(from: adViewControllerRepresentable.viewController)
        }
      }
      .alert("성과 출생지를 확인해 주세요", isPresented: $showingPopover) {
        Button("OK", role: .cancel){
          showingPopover = false
        }
      }
      .alert("저장되었습니다", isPresented:  $showingOk) {
        Button("OK"){
          register()
          coordinator.showAd(from: adViewControllerRepresentable.viewController)
          showingOk = false
        }
      }
//      .alert("설치 후 한 달 안에 등록해야 합니다.", isPresented: $showingReinstall) {
//        Button("OK", role: .cancel){}
//      }

//        .foregroundColor(
//          viewModel.canCreate
//            ? Colors.Accent.Content.primary
//            : Colors.Neutral.Content.disabled)
//        .disabled(!viewModel.canCreate))
    ).onAppear() {
      coordinator.loadAd()
    }
  }
}


var registeredImage : Image?
func setRegisteredImage(_ newImage: Image) {
  registeredImage = newImage
}

func getRegisteredImage() -> Image {
  if registeredImage == nil {
    if let image = RegisterInfo.obj.image {
      registeredImage = Image(uiImage: UIImage(data: image)!)
    } else {
      registeredImage = Image("sunny")
    }
  }

  return registeredImage!
}

func register() {
  RegisterInfo.obj = pendingRegisterInfo

  // store info
  let defaults = UserDefaults.standard
  defaults.setValue(RegisterInfo.obj.surName, forKey: RegisterInfoKeys.surName)
  defaults.setValue(RegisterInfo.obj.surNameHanja, forKey: RegisterInfoKeys.surNameH)
  defaults.setValue(RegisterInfo.obj.datetime, forKey: RegisterInfoKeys.dob)
  defaults.setValue(RegisterInfo.obj.gender.rawValue, forKey: RegisterInfoKeys.gender)
  defaults.setValue(RegisterInfo.obj.birthPlace, forKey: RegisterInfoKeys.place)
  defaults.setValue(RegisterInfo.obj.latitude, forKey: RegisterInfoKeys.latitude)
  defaults.setValue(RegisterInfo.obj.longitude, forKey: RegisterInfoKeys.longitude)
  defaults.setValue(RegisterInfo.obj.image, forKey: RegisterInfoKeys.image)
  gEditCount -= 1
  defaults.setValue(String(gEditCount), forKey: RegisterInfoKeys.editCount)

  defaults.synchronize()

//  pendingRegisterInfo.longitude = 0
//  pendingRegisterInfo.latitude = 0
  // clear previously stored names
  //  clearElem()


  UIApplication.shared.open(URL(string: "featuresApp://hackathon.com/headsup")!)
}

func cancelRegister() {
  pendingRegisterInfo.longitude = 0
  pendingRegisterInfo.latitude = 0

  UIApplication.shared.open(URL(string: "featuresApp://hackathon.com/headsup")!)
}

struct RegisterView_Previews: PreviewProvider {
    static var previews: some View {
        RegisterView()
    }
}
