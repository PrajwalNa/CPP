// Workshop 8 - Smart Pointers

#include <memory>
#include <utility>
#include "DataBase.h"
#include "Profile.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
	DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& badProfiles) {
		DataBase<Profile> result;
		for (size_t i = 0; i < allProfiles.size(); i++) {
            bool found = false;
            for (size_t j = 0; j < badProfiles.size(); j++) {
                if (allProfiles[i].m_name.first_name == badProfiles[j].m_name.first_name && allProfiles[i].m_name.last_name == badProfiles[j].m_name.last_name && allProfiles[i].m_age == badProfiles[j].m_age) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                Profile* newProfile = new Profile(allProfiles[i].m_name,allProfiles[i].m_address,allProfiles[i].m_age);
                newProfile->validateAddress();
                result += newProfile;
                delete newProfile;
                newProfile = nullptr;
            }
        }
		return result;
	}
	
	DataBase<Profile> excludeSmart(const DataBase<Profile>& allProfiles, const DataBase<Profile>& badProfiles) {
		DataBase<Profile> result;
		for (size_t i = 0; i < allProfiles.size(); i++) {
            bool found = false;
            for (size_t j = 0; j < badProfiles.size(); j++) {
                if (allProfiles[i].m_name.first_name == badProfiles[j].m_name.first_name && allProfiles[i].m_name.last_name == badProfiles[j].m_name.last_name && allProfiles[i].m_age == badProfiles[j].m_age) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                unique_ptr <Profile> newProfile (new Profile (allProfiles[i].m_name,allProfiles[i].m_address,allProfiles[i].m_age));
                newProfile->validateAddress();
                result += newProfile;
            }
        }
		return result;
	}
}