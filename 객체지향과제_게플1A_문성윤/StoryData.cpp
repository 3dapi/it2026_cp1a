// Scenario dialogue from doc/시나리오_1부_서준.md and doc/시나리오_2부_서준.md. CP949.
#include "StoryData.h"
#include <array>

namespace
{
const std::array<StorySection, static_cast<std::size_t>(StoryBlock::Count)> Sections{{
    // Prologue
    {"프롤로그", 0, {
        {"0:P-D01:1", "서준", "사흘째 같은 시간, 같은 장소. 그냥 지나치기에는 너무 정확하네.", StoryVisual::Empty, StoryCondition::Always, StoryEvent::None},
        {"0:P-D02:1", "서준", "이번에도 이름만 부르면 돌아간다. 무슨 일인지 확인만 하고 나오는 거야.", StoryVisual::Empty, StoryCondition::Always, StoryEvent::None},
        {"0:P-D03:1", "???", "……서준.", StoryVisual::Empty, StoryCondition::Always, StoryEvent::None},
        {"0:P-D04:1", "서준", "내 이름까지 아는 건 확실하고.", StoryVisual::Empty, StoryCondition::Always, StoryEvent::None},
        {"0:P-D05:1", "???", "들리면…… 이쪽으로 와 줘.", StoryVisual::Empty, StoryCondition::Always, StoryEvent::None},
        {"0:P-D06:1", "서준", "목소리는 움직이지 않아. 적어도 나를 따라붙는 쪽은 아니네.", StoryVisual::Empty, StoryCondition::Always, StoryEvent::None},
        {"0:P-D07:1", "서준", "거기 있었구나.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"0:P-D08:1", "서연", "너…… 지금 나를 보고 말한 거야?", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
    }, StoryBlock::Meeting},
    // Meeting
    {"서연과 첫 대화", 1, {
        {"1:D01:1", "서연", "정말 내가 보이는구나. 사흘 동안 불렀는데 아무도 한 번도 멈추지 않았어.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"1:D02:1", "서준", "보이는 것만으로 여기까지 들어온 건 아니야. 왜 내 이름을 알고\n있었는지부터 말해 줘.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"1:D03:1", "서연", "첫날, 담장 앞에서 전화받을 때 네가 이름을 말했어. 그때 내 쪽을\n돌아보길래… 혹시 들리는 걸까 했어.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"1:D04:1", "서준", "내가 귀신을 볼 수 있다는 걸 알고 부른 건 아니네.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"1:D05:1", "서연", "응. 그냥…… 네가 나를 지나치지 않을 것 같았어.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"1:D06:1", "서준", "그 기대만으로 위험한 폐교에 사람을 불렀다면, 부탁 정도는 제대로\n설명해야겠지.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"1:D07:1", "서연", "미안해. 내가 기억하는 게 많지 않아. 이름은 서연이고, 교실로 돌아가야\n한다는 것만 확실해.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"1:D08:1", "서준", "왜 돌아가야 하는데?", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"1:D09:1", "서연", "누군가한테 사과해야 해. 내가 그 애를 두고 먼저 도망친 것 같아.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"1:D10:1", "서준", "도망쳤는데 넌 왜 아직 여기 있어?", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"1:D11:1", "서연", "그걸 모르겠어. 나는 교실 안에 남아 있었던 것 같기도 해.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"1:D12:1", "서준", "둘 다 사실일 수는 없겠네. 적어도 네가 기억한 사건과 네가 내린 결론 중\n하나는 틀렸어.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"1:D13:1", "서연", "내가 누군가를 문 쪽으로 밀었어. 그 장면만 생각하면 내가 그 애를 버린\n것 같아.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"1:D14:1", "서준", "밀었다는 행동만 기억나고, 왜 밀었는지는 기억 안 난다는 거지?", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"1:D15:1", "서연", "응. 그래서 더 무서워. 이유를 잊은 건지, 이유 같은 건 애초에 없었던\n건지 모르겠어.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"1:D16:1", "서준", "좋아. 그럼 기억나는 사실과 네 추측을 따로 보자. 내가 찾은 증거랑\n맞는지도 확인하고.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"1:D17:1", "서연", "그래 줘. 내가 정말 잘못했다면 도망치지 않을게. 대신 내가 잘못 기억하고\n있다면 그것도 알려 줘.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"1:D18:1", "서연", "복도 보관함에 사진이 있었어. 그리고 교실에서는…… 누군가 손을 잡았던\n감각이 남아 있어.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
    }, StoryBlock::Count, StoryChoice::FirstTrust, {"서연의 말을 우선 믿고 조사한다.", "증거를 확인하기 전까지 판단을 보류한다."},
        {StoryBlock::TrustA, StoryBlock::TrustB}},
    // TrustA
    {"서연과 첫 대화", 1, {
        {"1:D19A:1", "서준", "그럼 우선 네 말을 믿고 따라가 볼게. 다만 중간에 이상한 점이 나오면\n바로 확인한다.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"1:D20A:1", "서연", "고마워. 내가 틀렸더라도 끝까지 같이 확인해 줘.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
    }, StoryBlock::Locker},
    // TrustB
    {"서연과 첫 대화", 1, {
        {"1:D19B:1", "서준", "도와주긴 할게. 하지만 판단은 증거를 본 다음이야. 네 기억부터 의심할\n수도 있어.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"1:D20B:1", "서연", "그래. 나도 내 기억이 무조건 맞다고 말할 자신은 없어.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
    }, StoryBlock::Locker},
    // Locker
    {"안내대와 보관함", 2, {
        {"2:D21:1", "서연", "잠깐. 안내대 서랍 안쪽에 뭔가 있었던 것 같아.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"2:D22:1", "서준", "방금 떠오른 거야?", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"2:D23:1", "서연", "응. 보관함을 생각하니까 같이 떠올랐어. 작은 금속 소리도 들렸던 것\n같고.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"2:D24:1", "서준", "열쇠 하나 있네. 이 정도면 기억이 완전히 뒤섞인 건 아니야.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::Key},
        {"2:D25:1", "서연", "그럼 사진도 진짜 있을까?", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"2:D26:1", "서준", "열쇠가 맞았다고 사진 내용까지 맞는 건 아니지. 직접 보면 돼.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"2:D27:1", "서연", "이상해. 가까이 오니까 열어야 한다는 생각보다 열면 안 된다는 느낌이 더\n강해.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"2:D28:1", "서준", "네 기억이 막는 건지, 다른 누가 막는 건지는 아직 모르겠네.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"2:D29:1", "서연", "다른 누가?", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"2:D30:1", "서준", "네가 사흘 동안 여기 있었는데도 기억이 계속 같은 부분에서 끊긴다면,\n가능성은 열어 둬야지.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
    }, StoryBlock::Count, StoryChoice::Locker, {"열쇠로 보관함을 연다.", "지금은 지나간다."},
        {StoryBlock::OpenLocker, StoryBlock::SkipLocker}},
    // OpenLocker
    {"안내대와 보관함", 2, {
        {"2:D31A:1", "서준", "연다. 여기까지 왔는데 안에 뭐가 있는지 확인 안 하고 갈 이유는 없어.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"2:OPEN:1", "시스템", "열쇠로 보관함을 열었다. +20점", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::LockerOpened},
        {"2:PHOTO:1", "시스템", "핵심 단서 사진을 획득했다. +20점", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::Photo},
        {"2:D32A:1", "서연", "……사진이야. 뒤에 사고 날짜가 적혀 있어. 저건 나고, 앞에 있는 애는 내\n친구야.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"2:D33A:1", "서준", "네가 친구 등을 문 바깥쪽으로 밀고 있어. 네가 먼저 도망친 장면은\n아닌데.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"2:D34A:1", "서연", "그럼 왜 나는 같이 안 나갔지? 사진 다음이 하나도 안 떠올라.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"2:D35A:1", "서준", "적어도 하나는 정정할 수 있어. 이 장면만 보고 네가 친구를 버렸다고\n단정할 수는 없어.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
    }, StoryBlock::Warning},
    // SkipLocker
    {"안내대와 보관함", 2, {
        {"2:D31B:1", "서준", "지금은 지나가자. 안에 뭐가 있는지는 모르는 채로 가는 거야.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"2:D32B:1", "서연", "알겠어. 그런데 저 안에 뭔가 있다는 느낌은 잊지 않을게.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"2:D33B:1", "서준", "좋아. 대신 지금은 확인하지 않은 걸 확인한 것처럼 생각하지 마.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
    }, StoryBlock::Warning},
    // Warning
    {"그림자의 경고", 3, {
        {"3:D34:1", "그림자", "돌아가. 산 사람이 여기서 더 알아낼 건 없다.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"3:D35:1", "서연", "저 목소리…….", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"3:D36:1", "서준", "아는 목소리야?", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"3:D37:1", "서연", "얼굴은 기억 안 나. 그런데 저 목소리를 들으면 내가 친구를 밀어내던\n장면이 계속 떠올라.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"3:D38:1", "그림자", "저 아이는 친구를 버렸다. 기억이 없다고 죄까지 사라지는 건 아니지.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"3:D39:1", "서준", "서연이 친구를 버렸다는 걸 네가 어떻게 확신해?", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"3:D40:1", "그림자", "저 아이가 알고 있으니까. 그래서 아직 이곳을 떠나지 못한다.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"3:D41:1", "서준", "그런데 왜 우리가 확인하려는 건 막지? 사실이면 증거를 봐도 달라질 게\n없을 텐데.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"3:D42:1", "그림자", "진실은 언제나 사람을 구하는 게 아니다. 모르는 편이 나은 기억도 있다.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"3:D43A:1", "서준", "사진은 네 말과 다르던데. 서연은 친구를 밖으로 밀어 주고 있었어.", StoryVisual::Both, StoryCondition::HasPhoto, StoryEvent::None},
        {"3:D43B:1", "서준", "증거가 없다고 네 말을 사실로 받아들일 생각은 없어. 교실까지 확인할\n거야.", StoryVisual::Both, StoryCondition::NoPhoto, StoryEvent::None},
        {"3:D44:1", "그림자", "쓸데없는 짓이다.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"3:D45:1", "서준", "방금 대답을 피했네. 네가 막고 싶은 게 기억 자체인지, 기억이 바뀌는\n건지는 아직 모르겠지만.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"3:D46:1", "그림자", "교실에 들어오면 후회할 거다.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"3:D47:1", "서연", "서준, 그만해도 돼. 처음엔 내가 부탁했지만, 네가 다치면서까지 확인할\n일은 아니야.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"3:D48:1", "서준", "여기서 멈추면 저 말만 남아. 대신 위험해 보이면 내가 판단할게. 네가\n미안해서 대신 결정하지는 마.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"3:D49:1", "서연", "……알겠어. 그럼 나도 기억나는 걸 숨기지 않을게.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
    }, StoryBlock::Floor},
    // Floor
    {"교실 입구", 4, {
        {"4:D50:1", "서연", "멈춰. 바로 앞은 밟지 마.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"4:D51:1", "서준", "기억났어?", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"4:D52:1", "서연", "응. 누군가 손을 잡고 벽 쪽으로 붙어서 지나갔어. 뒤에서 바닥이 무너지는\n소리도 났고.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"4:D53:1", "서준", "그럼 적어도 그때까지는 네가 혼자 도망친 게 아니네.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"4:D54:1", "서연", "그런데 그다음에 내가 그 애를 문 쪽으로 밀었어. 거기서 다시 끊겨.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"4:D55:1", "서준", "좋아. 여기부터는 기억하고 실제 바닥이 맞는지 같이 보자.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
    }, StoryBlock::Count, StoryChoice::Floor, {"서연의 기억을 믿고 벽 쪽으로 돌아간다.", "바로 건너가 직접 확인한다."},
        {StoryBlock::SafeFloor, StoryBlock::RiskyFloor}},
    // SafeFloor
    {"교실 입구", 4, {
        {"4:D56A:1", "서준", "네가 기억한 길로 간다. 벽 쪽부터 확인하자.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"4:D57A:1", "서연", "여기야. 이쪽은 발을 딛지 않았던 것 같아.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"4:D58A:1", "서준", "맞았네. 가운데는 이미 내려앉고 있어.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"4:D59A:1", "서연", "내 기억이…… 이번에는 누군가를 다치게 한 게 아니라 피하게 했네.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"4:SAFE:1", "시스템", "서연이 알려 준 길로 돌아갔다. +20점", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::SafeFloor},
    }, StoryBlock::ClassroomEntrance},
    // RiskyFloor
    {"교실 입구", 4, {
        {"4:D56B:1", "서준", "앞을 직접 확인할게. 한 번에 건너면--", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"4:D57B:1", "시스템", "깨진 바닥에 발을 헛디뎠다. HP -20.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::FloorDamage},
        {"4:D58B:1", "서연", "서준! 내 말을 못 믿는 건 괜찮아. 그래도 다치면서 확인하지는 마.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"4:D59B:1", "서준", "그건 인정할게. 확인하는 방법을 잘못 골랐어.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
    }, StoryBlock::ClassroomEntrance},
    // ClassroomEntrance
    {"교실 입구", 4, {
        {"4:D60:1", "서연", "교실 안에 기록철이 보여. 저걸 보면…… 그다음이 기억날 것 같아.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"4:D61:1", "서준", "지금까지 확실한 건 네 기억이 전부 거짓은 아니라는 것, 그리고 그림자가\n그중 일부만 골라 보여 줬다는 거야.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"4:D62:1", "서연", "그럼 저 안에 있는 것도 같이 확인해 줘.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"4:D63:1", "서준", "여기까지 왔으니 끝까지 본다. 대신 무슨 내용이 나오든 먼저 사실부터\n확인하자.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
    }, StoryBlock::Classroom},
    // Classroom
    {"사고 기록 조사", 5, {
        {"5:D64:1", "서연", "여기야. 내가 계속 돌아와야 한다고 생각했던 곳.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"5:D65:1", "서준", "기억나는 게 생겼어?", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"5:D66:1", "서연", "장면보다는 감각이 먼저 와. 저 문을 등지고 있었고, 누군가를 밖으로 보낸\n뒤에도 안쪽을 보고 있었어.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"5:D67:1", "서준", "지금은 그 이상 떠올리려고 하지 마. 먼저 남아 있는 걸 확인하자.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"5:D68:1", "서연", "일부러 기억하지 말라는 거야?", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"5:D69:1", "서준", "그림자가 네 기억을 건드렸다면, 억지로 떠올리는 순간 또 걔가 원하는\n장면만 볼 수도 있어.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"5:D70:1", "서연", "……맞아. 복도에서도 항상 같은 부분만 떠올랐으니까.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"5:D71:1", "서준", "여기 기록철 날짜가 사고 당일이야. 이건 네 기억이 아니라 실제로 남은\n기록이고.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"5:D72:1", "서연", "읽으면 내가 뭘 했는지 나올까?", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"5:D73:1", "서준", "적어도 누가 구조됐고 누가 남았는지는 확인할 수 있겠지.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"5:D74A:1", "서준", "사진 속 문 위치도 여기랑 맞아. 네 친구는 밖으로 향하고 있었고, 넌 교실\n안쪽에 남아 있었어.", StoryVisual::Seoyeon, StoryCondition::HasPhoto, StoryEvent::None},
        {"5:D74B:1", "서준", "사진은 없으니까 지금은 단정하지 말자. 기록이 말해 주는 범위까지만\n확인하면 돼.", StoryVisual::Seoyeon, StoryCondition::NoPhoto, StoryEvent::None},
        {"5:D75:1", "서연", "저 뒤쪽 장…… 이상하게 보기 싫어.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"5:D76:1", "서준", "네가 보기 싫은 건지, 누가 그렇게 느끼게 하는 건지 구분해야겠네.", StoryVisual::Seoyeon, StoryCondition::Always, StoryEvent::None},
        {"5:D77:1", "그림자", "그만둬.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"5:D78:1", "서연", "또 왔어.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"5:D79:1", "그림자", "그 종이를 읽는다고 달라지는 건 없다. 저 아이가 한 일은 이미 끝났다.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"5:D80:1", "서준", "끝난 일인데 기록 하나 읽는 건 왜 이렇게 싫어해?", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"5:D81:1", "그림자", "저 아이가 견딜 수 없으니까.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"5:D82:1", "서준", "서연이 견딜 수 없는지 네가 사라지는 게 싫은지는 아직 모르겠네.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
    }, StoryBlock::Count, StoryChoice::Record, {"기록을 끝까지 읽는다.", "기록을 놓고 그림자와 맞선다."},
        {StoryBlock::ReadRecord, StoryBlock::LeaveRecord}},
    // ReadRecord
    {"사고 기록 조사", 5, {
        {"5:D83A:1", "서준", "읽을 거야. 서연이 감당할 수 있는지는 서연이 정할 일이지, 네가 정할\n일이 아니야.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"5:D84A:1", "시스템", "사고 당일의 기록을 확인했다. 핵심 단서 ‘사고 기록’을 획득했다. +20점", StoryVisual::Both, StoryCondition::Always, StoryEvent::Record},
        {"5:D85A:1", "서준", "여기 있다. ‘동행 학생은 복도에서 구조됨. 서연은 교실 내부에서\n돌아오지 못함.’", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"5:D86A:1", "서연", "친구는…… 밖으로 나갔어?", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"5:D87A:1", "서준", "응. 적어도 네가 친구를 버리고 먼저 도망쳤다는 기록은 아니야.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"5:D88A:1", "서연", "그럼 나는 왜 남았지?", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"5:D89A:1", "그림자", "읽지 말라고 했을 텐데.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
    }, StoryBlock::Truth},
    // LeaveRecord
    {"사고 기록 조사", 5, {
        {"5:D83B:1", "서준", "손이 너무 가까워. 기록을 놓고 물러나!", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"5:D84B:1", "서연", "종이가… 부서졌어. 뒤쪽은 읽지도 못했는데.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"5:D85B:1", "서준", "미안해. 저 부분은 이제 읽을 수 없겠어.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"5:D86B:1", "그림자", "결국 너도 두려운 거다. 진실을 읽는 것보다 나와 싸우는 편이 쉬우니까.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"5:D87B:1", "서준", "내가 놓친 건 맞아. 그렇다고 네 말을 믿겠다는 뜻은 아니야.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"5:D88B:1", "그림자", "말이 많군.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
    }, StoryBlock::Truth},
    // Truth
    {"그림자의 정체", 6, {
        {"6:D90:1", "서연", "기억났어. 저 목소리, 사고가 나기 전에는 들은 적이 없어.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"6:D91:1", "서준", "그럼 그림자는 그날 같이 있던 사람이 아니야.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"6:D92:1", "그림자", "그게 중요하나? 저 아이는 이미 자신이 무슨 짓을 했는지 알고 있었다.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"6:D93:1", "서연", "아니. 나는 몰랐어. 네가 계속 ‘버렸다’고 말해서 그게 내 기억인 줄\n알았던 거야.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"6:D94:1", "그림자", "나는 없는 기억을 만든 적이 없다. 네가 가장 두려워한 생각을 들려줬을\n뿐이다.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"6:D95:1", "서준", "그게 더 분명하네. 사실을 알려 준 게 아니라 한 가지 해석만 반복한\n거잖아.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"6:D96A:1", "서준", "기록도 네 말과 달라. 친구는 구조됐고 서연은 교실에 남았어.", StoryVisual::Both, StoryCondition::HasRecord, StoryEvent::None},
        {"6:D96B:1", "서준", "기록은 아직 못 읽었어도 앞뒤가 안 맞아. 서연은 친구와 같이 위험한\n바닥을 지나 문까지 왔어.", StoryVisual::Both, StoryCondition::NoRecord, StoryEvent::None},
        {"6:D97:1", "서연", "내가 정말 잘못했을 수도 있어. 그래도 이제 그 결론을 네가 대신 정하게\n두지는 않을 거야.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
    }, StoryBlock::Count, StoryChoice::SecondTrust, {"기억은 같이 확인하자. 우리가 직접 본 것부터 믿자.", "지금은 그림자부터 막자."},
        {StoryBlock::SupportA, StoryBlock::SupportB}},
    // SupportA
    {"그림자의 정체", 6, {
        {"6:D98A:1", "서준", "그래. 기억은 우리 둘이 확인하자. 지금까지 직접 본 것부터 하나씩 맞추면\n돼.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"6:D99A:1", "서연", "응. 이번에는 내가 무서워하는 것보다 우리가 확인한 걸 먼저 믿어 볼게.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
    }, StoryBlock::Confrontation},
    // SupportB
    {"그림자의 정체", 6, {
        {"6:D98B:1", "서준", "지금은 저것부터 막자. 전투가 끝나면 남은 기억을 다시 확인해.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"6:D99B:1", "서연", "좋아. 대신 끝나고 나면 내 얘기도 그냥 덮어 두지 말아 줘.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
    }, StoryBlock::Confrontation},
    // Confrontation
    {"그림자의 정체", 6, {
        {"6:D100:1", "그림자", "그만해.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"6:D101:1", "서준", "왜? 서연이 자기 기억을 직접 판단하기 시작하니까 불편해?", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"6:D102:1", "그림자", "저 아이가 죄책감을 놓으면 나도 여기서 버틸 수 없다.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"6:D103:1", "서연", "그럼 넌 나를 지키려고 있던 게 아니었어.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"6:D104:1", "그림자", "나는 네가 버리지 못한 두려움이다. 네가 나를 버리면 나는 사라진다.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"6:D105:1", "서준", "그래서 진실을 막았구나. 서연이 계속 자신을 미워해야 네가 남을 수\n있으니까.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"6:D106:1", "그림자", "그 입부터 닫아 주지. 네가 가진 증거도, 저 아이가 붙잡은 희망도 전부\n여기서 없애겠다.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"6:D107:1", "서연", "서준, 조심해. 저게 움직일 때마다 아까보다 형태가 더 짙어져.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"6:D108:1", "서준", "괜찮아. 네가 할 일은 하나야. 떠오르는 게 있으면 말해 줘. 단서가 있으면\n같이 맞춰 보자.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
        {"6:D109:1", "서연", "알겠어. 이번에는 피하지 않을게.", StoryVisual::Both, StoryCondition::Always, StoryEvent::None},
    }, StoryBlock::Count},
    // AfterBattle
    {"그림자가 사라진 뒤", 8, {
        {"D110:1", "서준", "그림자는 사라졌어. 그런데 아직 한 가지는 남았어.", StoryVisual::Seoyeon},
        {"D111:1", "서연", "내가 그날 실제로 뭘 했는지.", StoryVisual::Seoyeon},
        {"D112:1", "서준", "응. 지금은 저 목소리 없이 기억할 수 있지?", StoryVisual::Seoyeon},
        {"D113:1", "서연", "친구 손을 잡고 깨진 바닥을 피했어. 문 앞까지 데려가서 그 애를 밖으로 밀었고…… 나는 바로 따라가지\n않았어.", StoryVisual::Seoyeon},
        {"D114:1", "서준", "지금 떠오른 건 거기까지구나. 다음은 서두르지 말자.", StoryVisual::Seoyeon},
        {"D115:1", "서연", "이상해. 예전에는 그다음에 바로 ‘내가 버렸다’는 생각이 들어왔는데, 지금은 그냥 빈칸이야.", StoryVisual::Seoyeon},
        {"D116:1", "서준", "그 빈칸을 억지로 채우지 말자. 우리가 가진 단서가 어디까지 말해 주는지부터 보자.", StoryVisual::Seoyeon},
    }, StoryBlock::Count},
    // GoodEnding
    {"마지막 단서", 8, {
        {"G01:1", "서준", "사진은 네가 친구를 밖으로 보낸 순간이고, 기록은 그 친구가 실제로 구조됐다는 결과야.", StoryVisual::Seoyeon},
        {"G02:1", "서연", "둘이 이어져…… 내가 그 애를 먼저 내보낸 거였어.", StoryVisual::Seoyeon},
        {"G03:1", "서연", "기억났어. 뒤쪽에 다른 사람이 남아 있을까 봐 돌아봤어. 친구한테 먼저 나가라고 하고.", StoryVisual::Seoyeon},
        {"G04:1", "서준", "그리고 넌 다시 문으로 돌아오지 못했어.", StoryVisual::Seoyeon},
        {"G05:1", "서연", "응. 도망친 게 아니었어. 그런데 왜 나는 그렇게 오래 내가 버렸다고 믿었을까.", StoryVisual::Seoyeon},
        {"G06:1", "서준", "무서웠으니까. 기억이 비어 있는 자리에 가장 나쁜 답이 먼저 들어갔고, 그림자가 그 답만 계속 들려줬고.", StoryVisual::Seoyeon},
        {"G07:1", "서연", "두려웠던 건 사실이지만, 그게 죄를 지었다는 증거는 아니었네.", StoryVisual::Seoyeon},
        {"G08:1", "서준", "그건 네가 지금 직접 확인한 결론이야.", StoryVisual::Seoyeon},
        {"G09:1", "서연", "처음에는 네가 그냥 나를 믿어 주면 괜찮아질 줄 알았어.", StoryVisual::Seoyeon},
        {"G10:1", "서연", "그런데 같이 의심하고, 확인하고, 틀린 부분을 고쳐 준 게 더 좋았어. 그래야 이 기억이 정말 내 것이 된\n것 같아.", StoryVisual::Seoyeon},
        {"G11:1", "서준", "그럼 이제 사과할 사람을 찾을 필요는 없겠네.", StoryVisual::Seoyeon},
        {"G12:1", "서연", "한 명은 있었어. 나 자신한테 너무 오래 잘못했다고 말했으니까.", StoryVisual::Seoyeon},
        {"G13:1", "서준", "그 사과는 네가 직접 해.", StoryVisual::Seoyeon},
        {"G14:1", "서연", "응. 그리고 서준한테는 고맙다고 할게.", StoryVisual::Seoyeon},
        {"G15:1", "서연", "내 마지막 단서를 찾아줘서 고마워.", StoryVisual::Seoyeon},
        {"G16:1", "서준", "잘 가, 서연.", StoryVisual::Seoyeon},
        {"G17:1", "서연", "이번에는 나도 저 문 밖으로 갈게.", StoryVisual::Seoyeon},
    }, StoryBlock::Count},
    // NormalEnding
    {"사실과 마음의 거리", 8, {
        {"N01:1", "서준", "사진하고 기록이 같은 일을 가리켜. 네가 친구를 버리고 먼저 달아난 건 아니야.", StoryVisual::Seoyeon},
        {"N02:1", "서연", "응. 이제 그건 알아.", StoryVisual::Seoyeon},
        {"N03:1", "서연", "그런데 이상하게 손에 남은 느낌은 아직 똑같아. 내가 그 애를 밀었다는 감각만 떠올리면 숨이 막혀.", StoryVisual::Seoyeon},
        {"N04:1", "서준", "사실을 안다고 감정이 바로 바뀌는 건 아니야.", StoryVisual::Seoyeon},
        {"N05:1", "서연", "그럼 아직 못 떠나도 괜찮을까?", StoryVisual::Seoyeon},
        {"N06:1", "서준", "오늘 알아낸 걸 다시 그림자한테 넘기지만 않으면 돼. 남은 건 천천히 네가 정리하면 되고.", StoryVisual::Seoyeon},
        {"N07:1", "서연", "예전 같으면 또 내가 벌을 받아야 한다고 생각했을 거야.", StoryVisual::Seoyeon},
        {"N08:1", "서연", "이제는 적어도 그 생각부터 의심해 볼 수 있을 것 같아.", StoryVisual::Seoyeon},
        {"N09:1", "서준", "그 정도면 오늘 한 일은 충분해.", StoryVisual::Seoyeon},
        {"N10:1", "서연", "다음에 다시 볼 수 있다면, 그때는 내가 먼저 이야기할게. 누가 대신 정해 주기 전에.", StoryVisual::Seoyeon},
        {"N11:1", "서준", "그래. 그때 듣지.", StoryVisual::Seoyeon},
        {"N12:1", "서연", "고마워, 서준.", StoryVisual::Seoyeon},
    }, StoryBlock::Count},
    // MissingCluesEnding
    {"확인하지 못한 빈칸", 8, {
        {"F01:1", "서준", "그림자는 사라졌어. 그래도 지금 가진 걸로는 그날 일을 끝까지 확인할 수 없어.", StoryVisual::Seoyeon},
        {"F02:1", "서연", "내가 친구를 버렸다는 말이 틀릴 수 있다는 건 알았는데…… 아니었다고 확실히 말할 수도 없는 거네.", StoryVisual::Seoyeon},
        {"F03:1", "서준", "응. 빈칸을 좋은 답으로 채워 주는 것도 결국 네 기억을 대신 정하는 일이야.", StoryVisual::Seoyeon},
        {"F04:1", "서연", "예전 같았으면 그런 말이 무서웠을 텐데.", StoryVisual::Seoyeon},
        {"F05:1", "서연", "지금은 차라리 괜찮아. 모르는 걸 안다고 믿는 것보다는.", StoryVisual::Seoyeon},
        {"F06:1", "서준", "보지 못한 부분이 남았어. 지금 가진 것만으로는 답할 수 없어.", StoryVisual::Seoyeon},
        {"F07:1", "서연", "알겠어. 이번에는 내가 결론을 먼저 정하지 않을게.", StoryVisual::Seoyeon},
        {"F08:1", "서준", "나도 모르는 걸 안다고 말하지 않을게.", StoryVisual::Seoyeon},
        {"F09:1", "서연", "고마워. 오늘은 여기까지면 돼.", StoryVisual::Seoyeon},
    }, StoryBlock::Count},
    // LifeLostEnding
    {"여기서 멈추는 조사", 8, {
        {"L01:1", "시스템", "Life가 모두 소진되었다.", StoryVisual::Seoyeon},
        {"L02:1", "서준", "아직…… 확인 못 한 게 있어.", StoryVisual::Seoyeon},
        {"L03:1", "서연", "아니. 이제 그만해.", StoryVisual::Seoyeon},
        {"L04:1", "서준", "서연.", StoryVisual::Seoyeon},
        {"L05:1", "서연", "처음엔 내가 너를 불렀어. 그러니까 이번에는 내가 끝내겠다고 말할게.", StoryVisual::Seoyeon},
        {"L06:1", "서연", "내 기억 때문에 네가 여기까지 남을 필요는 없어. 지금은 나가.", StoryVisual::Seoyeon},
        {"L07:1", "시스템", "조사를 계속할 수 없다.", StoryVisual::Seoyeon},
    }, StoryBlock::Count},
}};
} // namespace

const StorySection& GetStorySection(StoryBlock block)
{
    return Sections.at(static_cast<std::size_t>(block));
}

namespace
{
const std::array<std::vector<StoryLine>, static_cast<std::size_t>(BattleDialogue::Count)> BattleLines{{
    // Opening
    {
        {"B01:1", "시스템", "그림자의 손이 다가온다. 예상 피해 15.", StoryVisual::Both},
        {"B02:1", "그림자", "증거를 믿는다고 과거가 바뀌는 건 아니다.", StoryVisual::Both},
        {"B03:1", "서준", "과거를 바꾸려는 게 아니야. 네가 붙인 결론을 떼어내는 거지.", StoryVisual::Both},
        {"B04:1", "서연", "서준, 저 손이 먼저 와. 다음 움직임을 보고 골라.", StoryVisual::Both},
    },
    // Attack
    {
        {"B05:1", "시스템", "공격이 적중했다. 적 HP -20.", StoryVisual::Both},
        {"B06:1", "그림자", "그 정도로 나를 지울 수 있을 것 같나?", StoryVisual::Both},
    },
    // Defend
    {
        {"B07:1", "시스템", "방어 자세를 잡았다. 이번 공격 피해는 10.", StoryVisual::Both},
        {"B08:1", "서연", "버텼어. 다음 공격이 더 크게 모이면 무리해서 맞지 마.", StoryVisual::Both},
    },
    // Heal
    {
        {"B09:1", "시스템", "회복 아이템을 사용했다. HP가 최대 30 회복된다.", StoryVisual::Both},
        {"B10:1", "서준", "아직 끝낼 수 있어. 다음 움직임부터 다시 본다.", StoryVisual::Both},
    },
    // Photo
    {
        {"B11A:1", "서준", "이 사진을 봐. 서연은 친구보다 안쪽에 남아서 등을 문밖으로 밀고 있어. 먼저 버리고 달아난 사람이\n아니야.", StoryVisual::Both},
        {"B12A:1", "서연", "맞아. 이 장면은 이제 기억나. 나는 그 애를 밖으로 보내려고 밀었어.", StoryVisual::Both},
        {"B13A:1", "그림자", "그 다음을 모르면서 무엇을 안다고 말하지?", StoryVisual::Both},
        {"B14A:1", "시스템", "사진 속 행동이 그림자의 주장과 충돌한다. 적 HP -40.", StoryVisual::Both},
    },
    // Record
    {
        {"B11B:1", "서준", "사고 기록에는 친구가 구조됐고 서연이 교실에서 돌아오지 못했다고 남아 있어. 네가 말한 ‘먼저\n도망쳤다’와 반대야.", StoryVisual::Both},
        {"B12B:1", "서연", "내가 밖으로 나온 기억이 없었던 건 도망친 걸 잊어서가 아니었어. 정말 여기 남아 있었던 거야.", StoryVisual::Both},
        {"B13B:1", "그림자", "기록 몇 줄이 네 죄를 대신 판단해 줄 것 같나?", StoryVisual::Both},
        {"B14B:1", "시스템", "사고 기록이 그림자의 주장과 충돌한다. 적 HP -40.", StoryVisual::Both},
    },
    // BothClues
    {
        {"B11C:1", "서준", "사진은 서연이 친구를 문밖으로 보낸 순간을 남겼고, 기록은 그 친구가 구조됐다고 적었어. 행동하고\n결과가 이어져.", StoryVisual::Both},
        {"B12C:1", "서연", "그래. 내가 그 애를 버린 게 아니라 먼저 내보낸 거야. 그리고 나는 그 뒤에 교실에 남았어.", StoryVisual::Both},
        {"B13C:1", "그림자", "닥쳐. 네가 그렇게 믿는 순간에도 두려움은 사라지지 않는다.", StoryVisual::Both},
        {"B14C:1", "시스템", "두 단서가 같은 사건을 증명한다. 적 HP -40.", StoryVisual::Both},
    },
    // NormalForecast
    {
        {"B15:1", "시스템", "그림자의 손이 다가온다. 예상 피해 15.", StoryVisual::Both},
        {"B16:1", "서연", "손이 먼저 움직여. 크게 모으는 공격은 아니야.", StoryVisual::Both},
    },
    // StrongForecast
    {
        {"B17:1", "시스템", "어둠이 크게 모인다. 예상 피해 25.", StoryVisual::Both},
        {"B18:1", "서연", "이번 건 달라. 교실 전체의 어둠이 한쪽으로 모이고 있어.", StoryVisual::Both},
    },
    // NormalHit
    {{"B19:1", "시스템", "그림자의 공격을 받았다. HP -15.", StoryVisual::Both}},
    // StrongHit
    {{"B20:1", "시스템", "강한 충격을 받았다. HP -25.", StoryVisual::Both}},
    // BlockedHit
    {{"B21:1", "시스템", "방어로 충격을 줄였다. HP -10.", StoryVisual::Both}},
    // LowHP
    {
        {"LowHP1:1", "서연", "서준, 내 부탁 때문에 무리하지 마. 이기려고 쓰러지면 아무것도 확인 못 해.", StoryVisual::Both},
    },
    // ClueRelation
    {
        {"ClueRelation1:1", "서준", "들었지, 서연. 증거가 네 기억을 대신하는 게 아니라 네가 기억을 다시 볼 기준을 주는 거야.", StoryVisual::Both},
        {"ClueRelation2:1", "서연", "응. 이제 저 목소리가 먼저 결론을 말해도 그대로 믿지 않을게.", StoryVisual::Both},
    },
    // WeakEnemy
    {
        {"WeakEnemy1:1", "그림자", "왜 아직도 남아 있지? 저 아이가 나를 필요로 했기에 나는 생긴 거다.", StoryVisual::Both},
        {"WeakEnemy2:1", "서연", "필요했던 게 아니야. 무서워서 놓지 못했던 거야.", StoryVisual::Both},
    },
    // Retry
    {
        {"B26:1", "시스템", "HP가 0이 되었다. Life -1.", StoryVisual::Both},
        {"B27:1", "서연", "서준, 정신 차려. 다시 할 수 있으면 이번에는 공격 예고부터 보고 움직여.", StoryVisual::Both},
        {"B28:1", "시스템", "현재 구간 시작 상태로 돌아간다.", StoryVisual::Both},
    },
    // Victory
    {
        {"B22:1", "그림자", "내가 사라지면 네가 한 일을 혼자 견뎌야 한다.", StoryVisual::Both},
        {"B23:1", "서연", "그래도 네가 정해 준 죄를 붙잡고 있는 것보다는 나아.", StoryVisual::Both},
        {"B24:1", "서준", "끝이야.", StoryVisual::Both},
        {"B25:1", "시스템", "그림자가 흩어졌다. 전투 승리 +20점.", StoryVisual::Seoyeon},
    },
}};
}

const std::vector<StoryLine>& GetBattleDialogue(BattleDialogue dialogue)
{
    return BattleLines.at(static_cast<std::size_t>(dialogue));
}
